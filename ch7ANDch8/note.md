---

---

[TOC]

# 学习周报

## 第七讲&&第八讲 视觉里程计

### 基于特征点

#### 对极几何

对于单目相机，我们的问题可以抽象为

![image-20231028132531260](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231028132531260.png)

$I_1$ $I_2$ 分别表示两张图像，相机中心抽象为点$O_1$ $O_2$ 假设相机从点 $O_1$ 运动到点 $O_2$ 。相机对着同一个物体 $P$，在运动前后分别拍下了图像和 $I_1$和 $I_2$ 。物体 $P$ 在图像 $I_1$ 中的特征点是 $p_1$ ，在图像 $I_2$ 中的特征点是 $p_2$  。现在 $p_1$ ，$p_2$ 已知，并且知道二者是能够匹配的特征点，相机内参已知，其他一切未知，求解相机从 $O_1$ 到 $O_2$ 的运动。根据对极几何中的定义，图中 $O_1PO_2$ 平面为极平面，$O_1O_2$ 连线与像平面 $I_1，I_2$ 的交点 $e_1，e_2$ 称为极点 $O_1O_2$ 被称为基线，极平面与两个像平面的交线$l_1$，$l_2$ 称为极线。

- 回顾一下相机模型、内参外参、旋转矩阵

$$
ZX=KP
$$

其中$Z$缩放因子，$X$是三维齐次像素坐标，$K$是相机内参，$P$是相机系坐标
$$
ZP_{uv}=KTP_w
$$
其中 $P_{uv}$ 是三维齐次像素坐标，$T$是变换矩阵，$P_w$ 是世界坐标。这个式子中隐含了一次齐次坐标到非齐次坐标的转换。
$$
T=RP+t
$$
表示旋转矩阵和变换矩阵的关系

图中在第一帧的坐标系下，设$P=[X,Y,Z]$ ，则 $s_{1}p_{1}=K P,s_{2}p_{2}=K(R P+t)$ 代表两帧的相机模型，消掉常数因子 $s_1,s_2$ 再写成齐次坐标可得，$p_{1}=K P,p_{2}=K(R P+t)$ 。令$x_{1}=K^{-1}p_{1},x_{2}=K^{-1}p_{2}$ ，则 $x_2=Rx_1+t$ ，则
$$
t^{\wedge}x_{2}=t^{\wedge}R x_{1}+t^{\wedge}t=t^{\wedge}R x_{1} \\
x_2^{T}t^{\wedge}x_2=x_2^TtRx_1
$$
又，向量 $x_2^T$ 垂直于 $t^{\wedge}x_2$ ，所以
$$
x_{2}^{T}t^{\wedge}R x_{1}=0
$$
也即
$$
p_{2}^{T}K^{-T}t^{\wedge}R K^{-1}p_{1}=0
$$
把中间部分记为基础矩阵 $F$ 和 $E$ 则
$$
E=t^{\wedge}R,\quad F=K^{-1}E K^{-1},\quad x_{2}^{\dagger}E x_{1}=p_{2}^{\dagger}F p_{1}=0.
$$

#### DLT求解PnP

对于空间点P，假设齐次坐标为$P=(X,Y,Z,1)^{T}$ 在图像1中投影得到的特征点坐标为$x_1=(u_1,v_1,1)^T$已知P和$x_1$,求解R，t。

定义增广矩阵
$$
s\begin{pmatrix}u_1\\v_1\\1\end{pmatrix}=\begin{pmatrix}t_1&t_2&t_3&t_4\\t_5&t_6&t_7&t_8\\t_9&t_{10}&t_{11}&t_{12}\end{pmatrix}\begin{pmatrix}X\\Y\\Z\\1\end{pmatrix}
$$
则有
$$
u_1=\frac{t_1X+t_2Y+t_3Z+t_4}{t_9X+t_{10}Y+t_{11}Z+t_{12}}~~~~~~~~v_1=\frac{t_5X+t_6Y+t_7Z+t_8}{t_9X+t_{10}Y+t_{11}Z+t_{12}}
$$
定义
$$
\boldsymbol{t}_1=(t_1,t_2,t_3,t_4)^T,\boldsymbol{t}_2=(t_5,t_6,t_7,t_8)^T,\boldsymbol{t}_3=(t_9,t_{10},t_{11},t_{12})^T,
$$
有 $t_{1}^{T}P-t_{3}^{T}Pu_{1}=0,t_{2}^{T}P-t_{3}^{T}Pv_{1}=0$ 成立。类似地，每个特征点都可以写出两个方程，求解线性方程组可以得到T=[R|t]的解。但是得到的解是一般矩阵，需要对R进行QR分解，得到满足SE(3)的矩阵。这种方法需要使用6对匹配点。

#### BA求解PnP

Bundle Adjustment的思想是通过最小化重投影误差，求解位姿。前面说的线性方法，往往是先求相机位姿，再求空间点位置，而非线性优化则是把它们都看成优化变量，放在一起优化。这是一种非常通用的求解方式，我们可以用它对PnP或ICP给出的结果进行优化。这一类把相机和三维点放在一起进行最小化的问题，统称为Bundle Adjustment。

考虑相机模型
$$
s_i\boldsymbol{p}_i=KTP_i.
$$
将3D点的投影位置与观测位置作差，构建最小二程问题：
$$
T^*=\arg\min_{\boldsymbol{T}}\frac{1}{2}\sum_{i=1}^{n}\left\|\boldsymbol{u}_{i}-\frac{1}{s_{i}}\boldsymbol{KTP}_{i}\right\|_{2}^{2}
$$
先前我们估计相机的位姿都是先对于物理实际物体做detection，然后根据我们识别出的ROI与物理实体做匹配，从而估计相机，BA求解PnP的意思就是这时候其实detection会有一个误差，之前的方法都是完全信任detection的结果，而根据上式就可以看出，我们把相机的内外惨以及detection的结果一起作为优化目标，最后的效果是整体误差的缩小，而每个点的误差通常都不会精确为零。

利用李代数的知识推导出误差的梯度从而迭代求解即可。
$$
\frac{\partial\boldsymbol{e}}{\partial\boldsymbol{P}}=-\begin{bmatrix}\dfrac{f_x}{Z'}&0&-\dfrac{f_xX'}{Z'2}\\\\0&\dfrac{f_y}{Z'}&-\dfrac{f_yY'}{Z'2}\end{bmatrix}\boldsymbol{R}.
$$

#### SVD求解ICP

要找到一个欧氏变换 $R 、t$ 使得
$$
\forall i,\boldsymbol{p}_i=R\boldsymbol{p}_i^{\prime}+\boldsymbol{t}
$$
构建最小二乘问题，求使误差平方和达到极小
$$
\min_{\boldsymbol{R},\boldsymbol{t}}\frac{1}{2}\sum_{i=1}^{n}\|(\boldsymbol{p}_{i}-(\boldsymbol{R}\boldsymbol{p}_{i}{'}+\boldsymbol{t}))\|_{2}^{2}
$$
首先，定义两组点的质心：
$$
\boldsymbol{p}=\dfrac{1}{n}\sum_{i=1}^{n}(\boldsymbol{p}_{i}),\quad\boldsymbol{p}'=\dfrac{1}{n}\sum_{i=1}^{n}(\boldsymbol{p}_{i}')
$$
则
$$
\begin{aligned}
\frac12\sum_{i=1}^n\left\|\boldsymbol{p}_i-(\boldsymbol{R}\boldsymbol{p}_i^{\prime}+\boldsymbol{t})\right\|^2& \left.=\frac12\sum_{i=1}^n\left\|\boldsymbol{p}_i-\boldsymbol{R}\boldsymbol{p}_i\right.^{\prime}-t-\boldsymbol{p}+\boldsymbol{R}\boldsymbol{p}^{\prime}+\boldsymbol{p}-\boldsymbol{R}\boldsymbol{p}^{\prime}\right\|^2  \\
&=\frac12\sum_{i=1}^n\left\|\left(\boldsymbol{p}_i-\boldsymbol{p}-\boldsymbol{R}\left(\boldsymbol{p}_i^{\prime}-\boldsymbol{p}^{\prime}\right)\right)+\left(\boldsymbol{p}-\boldsymbol{R}\boldsymbol{p}^{\prime}-\boldsymbol{t}\right)\right\|^2 \\
&\left.=\frac12\sum_{i=1}^n(\left\|\boldsymbol{p}_i-\boldsymbol{p}-\boldsymbol{R}\left(\boldsymbol{p}_i\right.^{\prime}-\boldsymbol{p}^{\prime}\right)\right\|^2+\left\|\boldsymbol{p}-\boldsymbol{R}\boldsymbol{p}^{\prime}-\boldsymbol{t}\right\|^2+ \\
&2(\boldsymbol{p}_i-\boldsymbol{p}-\boldsymbol{R}\left(\boldsymbol{p}_i^{\prime}-\boldsymbol{p}^{\prime}\right))^\mathrm{T}(\boldsymbol{p}-\boldsymbol{R}\boldsymbol{p}^{\prime}-\boldsymbol{t}))
\end{aligned}
$$
由于 $ (\boldsymbol{p}_i-\boldsymbol{p}-\boldsymbol{R}\left(\boldsymbol{p}_i^{\prime}-\boldsymbol{p}^{\prime}\right)) $ 求和后为零，则目标函数化简为
$$
\min_{\boldsymbol{R},\boldsymbol{t}}J=\frac{1}{2}\sum_{i=1}^{n}\left\|\boldsymbol{p}_{i}-\boldsymbol{p}-\boldsymbol{R}\left(\boldsymbol{p}_{i}^{\prime}-\boldsymbol{p}^{\prime}\right)\right\|^{2}+\left\|\boldsymbol{p}-\boldsymbol{R}\boldsymbol{p}^{\prime}-\boldsymbol{t}\right\|^{2}
$$
目标简化成两个平方项之和，可以分别对两个平方项进行求解，先求解左边得到R，带入到右边得到t。右边项只有为0时才能让目标函数最小，当求解得到R时，可以根据 $t^*=p-Rp^{\prime}.$ 计算t。将左边的平方项展开有：
$$
\frac{1}{2}\sum_{i=1}^{n}\left\|\boldsymbol{q}_{i}-\boldsymbol{R}\boldsymbol{q}_{i}^{\prime}\right\|^{2}=\frac{1}{2}\sum_{i=1}^{n}\boldsymbol{q}_{i}^{T}\boldsymbol{q}_{i}+\boldsymbol{q}_{i}^{\prime T}\boldsymbol{R}^{T}\boldsymbol{R}\boldsymbol{q}_{i}^{\prime}-2\boldsymbol{q}_{i}^{T}\boldsymbol{R}\boldsymbol{q}_{i}^{\prime}
$$
其中 $R^TR=I$ ，所以只有最后一项对结果有影响，整理得
$$
\sum_{i=1}^n-\boldsymbol{q}_i^\mathrm{T}R\boldsymbol{q}_i^{\prime}=\sum_{i=1}^n-\mathrm{tr}\left(R\boldsymbol{q}_i^{\prime}\boldsymbol{q}_i^\mathrm{T}\right)=-\mathrm{tr}\left(R\sum_{i=1}^n\boldsymbol{q}_i^{\prime}\boldsymbol{q}_i^\mathrm{T}\right)
$$
接下来根据参考文献中的证明，求得 $\boldsymbol{W}=\sum_{i=1}^n\boldsymbol{q}_i\boldsymbol{q}_i^{\prime\text{T}}$ 的SVD分解之后，令
$$
R=UV^T
$$
即为 $\boldsymbol{R}$ 的解，若$\boldsymbol{R}$ 的行列式为负，取$-\boldsymbol{R}$ 为最优值即可。

#### 非线性优化求解ICP

以迭代的方式去找最优值。该方法和PnP非常相似。以李代数表达位姿时，目标函数可以写成
$$
\min_{\boldsymbol{\xi}}=\frac{1}{2}\sum_{i=1}^{n}\|(\boldsymbol{p}_{i}-\exp\left(\boldsymbol{\xi}^{\wedge}\right)\boldsymbol{p}_{i}^{\prime})\|_{2}^{2}
$$
使用扰动模型求出目标函数的导数：
$$
\frac{\partial\boldsymbol{e}}{\partial\delta\boldsymbol{\xi}}=-\left(\exp\left(\boldsymbol{\xi}^{\wedge}\right)\boldsymbol{p}_{i}{'}\right)^{\odot}
$$

### 基于光流追踪角点运动

> 光流是一种描述像素随时间在图像之间运动的方法。

光流法中有一条基本假设：灰度不变假设：同一个空间点的像素灰度值，在各个图像中是固定不变的。

#### LK光流

对于t时刻位于(x,y)处的像素，我们设t+dt时刻它运动到(x+dz,y+dy)处。由于灰度不变，我们有
$$
\boldsymbol{I}(x+\mathrm dx,y+\mathrm dy,t+\mathrm dt)=\boldsymbol{I}(x,y,t)
$$
对左边进行泰勒展开，保留一阶项，得
$$
\boldsymbol{I}\left(x+\mathrm{d}x,y+\mathrm{d}y,t+\mathrm{d}t\right)\approx\boldsymbol{I}\left(x,y,t\right)+\frac{\partial\boldsymbol{I}}{\partial x}\mathrm{d}x+\frac{\partial\boldsymbol{I}}{\partial y}\mathrm{d}y+\frac{\partial\boldsymbol{I}}{\partial t}\mathrm{d}t
$$
因为我们假设了灰度不变，于是下一个时刻的灰度等于之前的灰度，从而：
$$
\begin{aligned}\frac{\partial\boldsymbol I}{\partial x}\mathrm{d}x+\frac{\partial\boldsymbol I}{\partial y}\mathrm{d}y+&\frac{\partial\boldsymbol I}{\partial t}\mathrm{d}t=0 \\
\frac{\partial\boldsymbol I}{\partial x}\frac{\mathrm{d}x}{\mathrm{d}t}+\frac{\partial\boldsymbol I}{\partial y}\frac{\mathrm{d}y}{\mathrm{d}t}&=-\frac{\partial\boldsymbol I}{\partial t}\end{aligned}
$$
其中dx/dt为像素在x轴上的运动速度，而dy/dt为y轴上的速度，把它们记为u,v。则
$$
I\left[\begin{array}{ll}
\boldsymbol{I}_{x} & \boldsymbol{I}_{y}
\end{array}\right]\left[\begin{array}{l}
u \\
v
\end{array}\right]=-\boldsymbol{I}_{t}
$$

> 在LK光流中，我们假设某一个窗口内的像素具有 相同的运动。

则对于一个大小为w×w的窗口，它含有w2数量的像素。则 $\begin{bmatrix}\boldsymbol{I}_x&\boldsymbol{I}_y\end{bmatrix}_k\begin{bmatrix}u\\\\v\end{bmatrix}=-\boldsymbol{I}_{tk},\quad k=1,\ldots,w^2$ 

根据约束求其最小二乘解即可。

#### 直接法求解角点运动

已知相机内参K，物体P的3D坐标，分别知道第1帧和第2帧上的投影坐标 $p_1, p_2$ ，但由于没有特征匹配的过程，所以不知道 $p_1$ 和 $p_2$ 是否对应同一个物体P。

第1帧的像素坐标为 $p_{1}=\frac{1}{Z_{1}}KP$ 第2帧的像素坐标为 $p_{2}=\frac{1}{Z_{2}}K(RP+t)=\frac{1}{Z_{2}}K(exp(\xi^{\wedge})P)_{1:3}$ 

同样构建最小二乘模型
$$
\min_{\boldsymbol{\xi}}J\left(\boldsymbol{\xi}\right)=\sum_{i=1}^{N}e_{i}^{T}e_{i},\quad e_{i}=\boldsymbol{I}_{1}\left(\boldsymbol{p}_{1,i}\right)-\boldsymbol{I}_{2}\left(\boldsymbol{p}_{2,i}\right)
$$
扰动模型求导：
$$
\begin{aligned}
e\left(\boldsymbol\xi\oplus\delta\boldsymbol\xi\right)& =\boldsymbol{I}_{1}\left(\frac{1}{Z_{1}}\boldsymbol{KP}\right)-\boldsymbol{I}_{2}\left(\frac{1}{Z_{2}}\boldsymbol{K}\exp\left(\delta\boldsymbol{\xi}^{\wedge}\right)\exp\left(\boldsymbol{\xi}^{\wedge}\right)\boldsymbol{P}\right)  \\
&\approx I_{1}\left(\frac{1}{Z_{1}}\boldsymbol{K}\boldsymbol{P}\right)-\boldsymbol{I}_{2}\left(\frac{1}{Z_{2}}\boldsymbol{K}\left(1+\delta\boldsymbol{\xi}^{\wedge}\right)\exp\left(\boldsymbol{\xi}^{\wedge}\right)\boldsymbol{P}\right) \\
&=I_{1}\left(\frac{1}{Z_{1}}\boldsymbol{K}\boldsymbol{P}\right)-I_{2}\left(\frac{1}{Z_{1}} \boldsymbol{K}\exp(\xi^{\wedge})\boldsymbol{P}+\frac{1}{Z_2}\boldsymbol{K}\delta\xi^{\wedge}\exp(\xi^{\wedge}\boldsymbol{P})
\right)
\end{aligned}
$$
定义中间变量 $q=\delta\xi^{\wedge}exp(\xi^{\wedge})P,u=\frac1{Z_2}Kq$ 
$$
\begin{aligned}
e\left(\boldsymbol{\xi}\oplus\delta\boldsymbol{\xi}\right)& =\boldsymbol{I}_{1}\left(\frac{1}{Z_{1}}\boldsymbol{K}\boldsymbol{P}\right)-\boldsymbol{I}_{2}\left(\frac{1}{Z_{2}}\boldsymbol{K}\exp\left(\boldsymbol{\xi}^{\wedge}\right)\boldsymbol{P}+\boldsymbol{u}\right)  \\
&\approx I_{1}\left(\frac{1}{Z_{1}}KP\right)-I_{2}\left(\frac{1}{Z_{2}}K\exp\left(\xi^{\wedge}\right)P\right)-\frac{\partial\boldsymbol{I}_{2}}{\partial\boldsymbol{u}}\frac{\partial\boldsymbol{u}}{\partial\boldsymbol{q}}\frac{\partial\boldsymbol{q}}{\partial\delta\boldsymbol{\xi}}\delta\boldsymbol{\xi} \\
&=e\left(\xi\right)-\frac{\partial\boldsymbol{I}_{2}}{\partial u}\frac{\partial\boldsymbol{u}}{\partial\boldsymbol{q}}\frac{\partial\boldsymbol{q}}{\partial\delta\boldsymbol{\xi}}\delta\boldsymbol{\xi}.
\end{aligned}
$$
最终得到雅可比阵其实是
$$
\frac{\partial\boldsymbol{q}}{\partial\delta\boldsymbol{\xi}}=[\boldsymbol{I},-\boldsymbol{q}^\wedge]
$$
根据雅各比矩阵进行迭代求解。

## 下周计划

本周内容侧重于数学推导，看懂了对极几何、PnP、ICP、光流他们到底在做什么，下周将使用g2o和ceres针对第七章的课后题编程实战进行突破。
