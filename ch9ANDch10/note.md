[TOC]


## 第9&10讲 后端

前端能够根据相邻的两幅图像判断出此时此刻的位姿，是暂时的；那么后端需要对前端测量以及计算的结果进行矫正，不仅用过去的信息，也用未来的信息更新自己，希望能够得到一个长时间的正确状态。

### 基于滤波的方法

高斯分布：如果一个随机变量$x$服从高斯分布$N(μ,\sigma^2)$,那么它的概率密度函数为
$$
p(x)=\frac{1}{\sqrt{2\pi}\sigma}\exp\left(-\frac{1}{2}\frac{(x-\mu)^2}{\sigma^2}\right)
$$
高维形式
$$
p(x)=\frac{1}{\sqrt{(2\pi)^{N}\det\left(\boldsymbol{\Sigma}\right)}}\exp\left(-\frac{1}{2}(\boldsymbol{x}-\boldsymbol{\mu})^{\mathrm{T}}\boldsymbol{\Sigma}^{-1}\left(\boldsymbol{x}-\boldsymbol{\mu}\right)\right)
$$
若考虑随机变量 $\boldsymbol{x}\sim N(\boldsymbol{\mu}_{x},\boldsymbol{\Sigma}_{xx})$ ，另一变量 $y$ 满足
$$
y=Ax+b+w
$$
其中$A$,$b$为线性变量的系数矩阵和偏移量，$w$为噪声项，为零均值的高斯分布：$w～N(0,R)$。 则$y$的分布为
$$
p\left(\boldsymbol{y}\right)=N\left(\boldsymbol{A}\boldsymbol{\mu}_{x}+b,\boldsymbol{R}+\boldsymbol{A}\boldsymbol{\Sigma}_{xx}\boldsymbol{A}^{\mathrm{T}}\right)
$$

#### KF观测器

把位姿和路标写在一起，记为 $\boldsymbol{x}_k\triangleq\{\boldsymbol{x}_k,\boldsymbol{y}_1,\ldots,\boldsymbol{y}_m\}$ ，则slam数学模型写为
$$
\left.\left\{\begin{array}{l}\boldsymbol{x}_k=f\left(\boldsymbol{x}_{k-1},\boldsymbol{u}_k\right)+\boldsymbol{w}_k\\\boldsymbol{z}_k=h\left(\boldsymbol{x}_k\right)+\boldsymbol{v}_k\end{array}\right.\right.~~~~~~~~~k=1,\ldots,N
$$
假设噪声服从零均值高斯分布，即 $\boldsymbol{w}_k\sim N(\mathbf{0},\boldsymbol{R}).\quad\boldsymbol{v}_k\sim N(\mathbf{0},\boldsymbol{Q})$ ，令 $ {\hat{x}}_{k}$ 表示后验， $\check{x}_k$ 表示先验

写出似然和先验的分布
$$
\begin{aligned}
&P\left(\boldsymbol{x}_k|\boldsymbol{x}_0,\boldsymbol{u}_{1:k},\boldsymbol{z}_{1:k-1}\right)=N\left(\boldsymbol{A}_k\hat{\boldsymbol{x}}_{k-1}+\boldsymbol{u}_k,\boldsymbol{A}_k\hat{\boldsymbol{P}}_{k-1}\boldsymbol{A}_k^T+\boldsymbol{R}\right) \\
&P\left(\boldsymbol{z}_{k}|\boldsymbol{x}_{k}\right)=N\left(\boldsymbol{C}_{k}\boldsymbol{x}_{k},\boldsymbol{Q}\right)
\end{aligned}
$$
把先验均值和方差记为 $\check{\boldsymbol{x}}_k=\boldsymbol{A}_k\hat{\boldsymbol{x}}_{k-1}+\boldsymbol{u}_k,\quad\check{\boldsymbol{P}}_k=\boldsymbol{A}_k\hat{\boldsymbol{P}}_{k-1}\boldsymbol{A}_k^T+\boldsymbol{R}$ 

则卡尔曼滤波器的维护可以分为预测和更新两个步骤：

![image-20231101155816986](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101155816986.png)

EKF滤波器实际上假设了系统具有马尔科夫性，实际上SLAM问题不完全满足这个条件。并且EKF只做了一阶的展开，实际上一阶展开不足以代表整个模型。并且EKF需要占用大量资源对状态量的均值和协方差进行存储。尽管我们认识到非线性优化比滤波器占有明显的优势，但是在计算资源受限，或待估计量比较简单的场合，EKF仍不失为一种有效的方式。

### 基于图优化的方法

#### BA问题建模

将位姿 $\boldsymbol T$ 和路标 $\boldsymbol p$ 放在一起优化，令自变量为 $\boldsymbol{x}=[T_1,\ldots,T_m,\boldsymbol{p}_1,\ldots,\boldsymbol{p}_n]^\mathrm{T}$ ，则目标函数写为：
$$
\begin{aligned}\frac{1}{2}\|f(x)^2\|=\frac{1}{2}\sum_{i=1}^{m}\sum_{j=1}^{n}\|e_{ij}\|^2&=\frac{1}{2}\sum_{i=1}^{m}\sum_{j=1}^{n}\|\boldsymbol{z}_{ij}-h(\boldsymbol{T}_i,\boldsymbol{p}_j)\|^2\end{aligned}
$$
增量方程：
$$
\frac12\left\|f(\boldsymbol{x}+\Delta\boldsymbol{x})\right\|^2\approx\frac12\sum_{i=1}^m\sum_{j=1}^n\left\|\boldsymbol{e}_{ij}+\boldsymbol{F}_{ij}\Delta\boldsymbol{\xi}_i+\boldsymbol{E}_{ij}\Delta\boldsymbol{p}_j\right\|^2
$$

#### $\boldsymbol J$ 和 $\boldsymbol H$ 的稀疏性与边缘化

对于代价函数中的 $e_{ij}$，描述的是在 $ \boldsymbol{\xi}_{i} $看到 $\boldsymbol p_j$ ，只与这两个量相关，所以 
$$
\boldsymbol{J}_{ij}(\boldsymbol{x})=\left(\boldsymbol{0}_{2\times6},\ldots\boldsymbol{0}_{2\times6},\frac{\partial\boldsymbol{e}_{ij}}{\partial\boldsymbol{\xi}_i},\boldsymbol{0}_{2\times6},\ldots\boldsymbol{0}_{2\times3},\ldots\boldsymbol{0}_{2\times3},\frac{\partial\boldsymbol{e}_{ij}}{\partial\boldsymbol{p}_j},\boldsymbol{0}_{2\times3},\ldots\boldsymbol{0}_{2\times3}\right)
$$
而 $\boldsymbol H=\boldsymbol  J^T\boldsymbol J$ ，所以只有在 $\boldsymbol H(i,j) \boldsymbol H(i,i) \boldsymbol H(j,j) \boldsymbol H(j,i)  $ 处有非零快，其中 $i$ 代表相机的贡献， $j$ 代表路标的贡献。

![image-20231101163130091](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101163130091.png)

而 $\boldsymbol J$ 的稀疏性又来源于，不是每个相机与路标都有关系，即不是每个位置都能观测到所有路标，只有能观测到的路标才会为非零值，下面这张彩图表示，假设一个场景内有 2个相机位姿($C_1,C_2$)和6个路标点($P_1,P_2,P_3,P_4,P_5,P_6$)。这些相机和点云所对应的变量为$T_i=1,2$及$p_j,j=1,⋯,6$。相机$C_1$观测到路标点$P_1,P_2,P_3,P_4$,相机$C_2$观测到路标点 $P_3,P_4,P_5,P_6$ 。相机和路标以圆形节点表示。如果$i$相机能够观测到$j$点，我们就在它们对应的节点连上一条边。

![image-20231101163529457](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101163529457.png)

场景下的BA目标函数为：
$$
\frac{1}{2}\left(\left\|e_{11}\right\|^2+\left\|e_{12}\right\|^2+\left\|e_{13}\right\|^2+\left\|e_{14}\right\|^2+\left\|e_{23}\right\|^2+\left\|e_{24}\right\|^2+\left\|e_{25}\right\|^2+\left\|e_{26}\right\|^2\right)
$$
则根据上图我们可以写出$C_1、P_1$的雅可比：
$$
J_{11}=\frac{\partial\boldsymbol{e}_{11}}{\partial\boldsymbol{x}}=\left(\frac{\partial\boldsymbol{e}_{11}}{\partial\boldsymbol{\xi}_1},\boldsymbol{0}_{2\times6},\frac{\partial\boldsymbol{e}_{11}}{\partial\boldsymbol{p}_1},\boldsymbol{0}_{2\times3},\boldsymbol{0}_{2\times3},\boldsymbol{0}_{2\times3},\boldsymbol{0}_{2\times3}\right)
$$
![image-20231101171352891](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101171352891.png)

整个目标函数的系数情况如下图：

![image-20231101171417225](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101171417225.png)

![image-20231101171515767](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101171515767.png)

#### Schur消元（边缘化）

将 $\boldsymbol H$ 分块

![image-20231101171757195](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231101171757195.png)

对应的线性方程组也可以由 $\boldsymbol H \Delta \boldsymbol x=\boldsymbol g$ 变为如下形式：
$$
\begin{bmatrix}B&E\\E^\mathrm{T}&C\end{bmatrix}\begin{bmatrix}\Delta x_\mathrm{c}\\\Delta x_p\end{bmatrix}=\begin{bmatrix}v\\w\end{bmatrix}
$$
其中 $B$ 、$C$ 为对角矩阵，利用高斯消元法解方程，
$$
\begin{aligned}&\begin{bmatrix}I&-EC^{-1}\\0&I\end{bmatrix}\begin{bmatrix}B&E\\E^{\mathbb{T}}&C\end{bmatrix}\begin{bmatrix}\Delta x_{\mathbb{C}}\\\Delta x_{p}\end{bmatrix}=\begin{bmatrix}I&-EC^{-1}\\0&I\end{bmatrix}\begin{bmatrix}v\\w\end{bmatrix}\\\\&\begin{bmatrix}B-EC^{-1}E^{\mathbb{T}}&0\\E^{\mathbb{T}}&C\end{bmatrix}\begin{bmatrix}\Delta x_{\mathbb{C}}\\\Delta x_{p}\end{bmatrix}=\begin{bmatrix}v-EC^{-1}w\\w\end{bmatrix}\end{aligned}
$$
方程组第一行变为和 $\Delta \boldsymbol x_p$ 无关的项，即可先求解第一行 $\Delta \boldsymbol x_c$ ，再带入第二行求解 $\Delta \boldsymbol x_p$ 即可。

#### 鲁棒核函数

BA中的目标函数每个误差项的贡献相当，如果某次观测出现了很大的异常值、离群值，那会对最后结果产生很大的影响，引入鲁棒核函数Huber kernal：
$$
H(e)=\begin{cases}\dfrac12e^2&\text{当}|e|\leqslant\delta,\\[2ex]\delta\left(|e|-\dfrac12\delta\right)&\text{其他}\end{cases}
$$
当误差e大于某个阈值δ后，函数增长由二次形式变成了一次形式，相当于限制 了梯度的最大值。同时，Huber核函数又是光滑的，可以很方便地求导。

### 滑动窗口和位姿图

#### 滑动窗口

删除一个关键帧时 $x_1$，相当于对 $x_1$ 边缘化，而与 $x_1$ 有关的路标点会产生先验信息，这会影响到 $H$ 的稀疏性，14讲中并未介绍具体做法，具体做法应该体现在工程实现中。

#### 位姿图的优化

假设只有IMU或者GPS的数据，此时只有位姿，没有路标点，仅对位姿进行优化不考虑路标点即位姿图优化。

假设 $\Delta\boldsymbol T_{ij}$ 表示 $\boldsymbol T_i$ 到 $\boldsymbol T_j$ 的位姿变换，则用李群、李代数表达：
$$
T_{ij}=T_{i}^{-1}T_{j}
\\
\Delta\boldsymbol{\xi}_{ij}=\boldsymbol{\xi}_i^{-1}\circ\boldsymbol{\xi}_j=\ln\left(\boldsymbol{T}_i^{-1}\boldsymbol{T}_j\right)^\vee
$$
左扰动模型
$$
\hat{\boldsymbol{e}}_{ij}=\ln\left(\boldsymbol{T}_{ij}^{-1}\boldsymbol{T}_{i}^{-1}\exp((-\boldsymbol{\delta}\boldsymbol{\xi}_{i})^{\wedge})\exp(\delta\boldsymbol{\xi}_{j}^{\wedge})\boldsymbol{T}_{j}\right)^{\vee}
$$
最后求导得出
$$
\boldsymbol e_ij \approx\boldsymbol{e}_{ij}+\frac{\partial\boldsymbol{e}_{ij}}{\partial\boldsymbol{\delta\xi}_{i}}\delta\boldsymbol{\xi}_{i}+\frac{\partial\boldsymbol{e}_{ij}}{\partial\boldsymbol{\delta\xi}_{j}}\boldsymbol{\delta\xi}_{j}
$$
其中
$$
\begin{aligned}\frac{\partial\boldsymbol{e}_{ij}}{\partial\boldsymbol{\delta\xi}_i}&=-\mathcal{J}_r^{-1}(\boldsymbol{e}_{ij})\mathrm{Ad}(\boldsymbol{T}_j^{-1})\\\frac{\partial\boldsymbol{e}_{ij}}{\partial\boldsymbol{\delta\xi}_j}&=\mathcal{J}_r^{-1}(\boldsymbol{e}_{ij})\mathrm{Ad}(\boldsymbol{T}_j^{-1})\end{aligned}
$$




