# 学习周报

[TOC]

### 矩阵对角化

若矩阵$A$ 有 $n$ 个线性无关的特征向量$[x_1~~~x_2\cdots x_n]$ （即$A$可逆），则$A$ 可以分解为 $ S^{-1}AS=\Lambda  $ 的形式，其中$S$ 为 $A$ 的特征向量矩阵，$\Lambda$ 为特征值组成的对角矩阵。

证明：由于$S$ 为 $A$ 的特征向量矩阵，则令$A$ 与特征向量矩阵相乘，利用特征向量与的性质：
$$
\begin{aligned}
AS& \left.=A\left[\begin{matrix}{\mathbf{x}_{1}}&{\mathbf{x}_{2}}&{\cdots}&{\mathbf{x}_{n}}\\\end{matrix}\right.\right]  \\
&\left.=\left[\begin{matrix}\lambda_1\mathbf{x}_1&\lambda_2\mathbf{x}_2&\cdots&\lambda_n\mathbf{x}_n\end{matrix}\right.\right] \\
&\left.=S\left[\begin{matrix}\lambda_1&0&\cdots&0\\0&\lambda_2&&0\\\vdots&&\ddots&\vdots\\0&\cdots&0&\lambda_n\end{matrix}\right.\right] \\
&\left.=S\Lambda\right.
\end{aligned}
$$
则 $ S^{-1}AS=\Lambda  $

### SVD

矩阵描述的是一种变换，奇异值分解是矩阵分解的其中一种。

<center>
    <img style="border-radius: 0.3125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" 
    src="https://charlesliuyx.github.io/2017/10/05/%E3%80%90%E7%9B%B4%E8%A7%82%E8%AF%A6%E8%A7%A3%E3%80%91%E4%BB%80%E4%B9%88%E6%98%AFPCA%E3%80%81SVD/SVD.svg" width = "75%" alt=""/>
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">
      SVD的几何意义
  	</div>
</center>

图中可以看出，SVD的几何意义即为将一个矩阵乘以一组正交基进行旋转，然后乘以对角矩阵进行缩放，然后再旋转的操作。相比于其他矩阵分解公式，SVD的优势在于$M$ 矩阵可以是任意矩阵，不要求其可逆，不要求其为方阵。

<center>
    <img style="border-radius: 0.3125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" 
    src="https://upload.wikimedia.org/wikipedia/commons/thumb/c/c8/Singular_value_decomposition_visualisation.svg/512px-Singular_value_decomposition_visualisation.svg.png" width = "75%" alt=""/>
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">
      SVD的几何意义
  	</div>
</center>

从上面两张图中可以看出，SVD是将一个矩阵分解为一组正交基乘以一个对角矩阵再乘以另一组正交基的操作，用矩阵语言来描述，即假设$V$ $U$ 为两组正交基，对于$r < n$ ，使得$Mv_r=\sigma_ru_r$ 成立，即
$$
\begin{aligned}
\left.M\left[\begin{array}{llll}{\mathbf{v}_{1}}&{\mathbf{v}_{2}}&{\cdots}&{\mathbf{v}_{r}}\end{array}\right.\right]& \left.=\left[\begin{array}{ccccc}\sigma_{1}\mathbf{u}_{1}&\sigma_{2}\mathbf{u}_{2}&\cdots&\sigma_{r}\mathbf{u}_{r}\\\end{array}\right.\right]  \\
&\left.=\left[\begin{array}{cccc}\mathbf{u}_1&\mathbf{u}_2&\cdots&\mathbf{u}_r\end{array}\right.\right]\left[\begin{array}{ccc}\sigma_1&&\\&\sigma_2&\\&&\ddots\\&&&\sigma_r\end{array}\right]
\end{aligned}
$$
即（利用正交矩阵的逆等于其转置）
$$
MV=U\Sigma~~~=>~~~M=U\Sigma V^T
$$
SVD可以用计算 $M^TM$ 和 $MM^T$ 的方式来求解
$$
\begin{align*}
  M^TM &= V\Sigma U^{-1}U\Sigma V^T \\
    &= V\Sigma^2 V^T \\
    &= V\left[ \begin{array}{ccc}\sigma^2_1&&\\&\sigma^2_2&\\&&\ddots\\&&&\sigma^2_r\end{array} \right] V^T
\end{align*}
$$
不难看出通过利用 $M^TM$ 将$M$ 转变为可逆矩阵，然后对其进行三角化分解即可，则得出结论：
$\Sigma$ 为$M^TM$ 的正交化后的特征值， $V$ 为 $M^TM$ 正交化后的特征向量，$U$ 为 $MM^T$ 正交化后的特征向量

### 矩阵求导

矩阵求导其实本质上就是多元函数求偏导，只是以矩阵的形式写出来了。

例如，对于 $f(x_1,x_2,x_3)=x_1^2+x_1x_2+x_2x_3$ 其导数为：
$$
\dfrac{\partial f(\boldsymbol{x})}{\partial\boldsymbol{x}_{3\times1}}=\begin{bmatrix}\frac{\partial f}{\partial x_1}\\\frac{\partial f}{\partial x_2}\\\frac{\partial f}{\partial x_3}\end{bmatrix}=\begin{bmatrix}2x_1+x_2\\x_1+x_3\\x_2\end{bmatrix}
$$
下面列出矩阵函数的几种形式

- 标量变元：

$$
\boldsymbol{f}_{3\times1}(x)=\begin{bmatrix}f_1(x)\\f_2(x)\\f_3(x)\end{bmatrix}=\begin{bmatrix}x+1\\2x+1\\3x^2+1\end{bmatrix}
\\
\boldsymbol{F}_{3\times2}(x)=\begin{bmatrix}f_{11}(x)&f_{12}(x)\\f_{21}(x)&f_{22}(x)\\f_{31}(x)&f_{32}(x)\end{bmatrix}=\begin{bmatrix}x+1&2x+2\\x^2+1&2x^2+1\\x^3+1&2x^3+1\end{bmatrix}
$$

- 向量变元：

设 $\boldsymbol{x}=[x_1,x_2,x_3]^T$ 
$$
\left.f_{3\times1}(\boldsymbol{x})=\left[\begin{array}{c}f_1(\boldsymbol{x})\\f_2(\boldsymbol{x})\\f_3(\boldsymbol{x})\end{array}\right.\right]=\left[\begin{array}{c}x_1+x_2+x_3\\x_1^2+2x_2+2x_3\\x_1x_2+x_2+x_3\end{array}\right]
\\
\left.\boldsymbol{F}_{3\times2}(\boldsymbol{x})=\left[\begin{matrix}f_{11}(\boldsymbol{x})&f_{12}(\boldsymbol{x})\\f_{21}(\boldsymbol{x})&f_{22}(\boldsymbol{x})\\f_{31}(\boldsymbol{x})&f_{32}(\boldsymbol{x})\end{matrix}\right.\right]=\left[\begin{matrix}2x_1+x_2+x_3&2x_1+2x_2+x_3\\2x_1+2x_2+x_3&x_1+2x_2+x_3\\2x_1+x_2+2x_3&x_1+2x_2+2x_3\end{matrix}\right]
$$

- 矩阵变元：

设 $\boldsymbol{X}_{3\times2}=\left(x_{ij}\right)_{i=1,j=1}^{3,2}$ ，可见在展开式中将$X$ 按行展开了。
$$
\boldsymbol{f}_{3\times1}(\boldsymbol{X})=\begin{bmatrix}f_1(\boldsymbol{X})\\f_2(\boldsymbol{X})\\f_3(\boldsymbol{X})\end{bmatrix}=\begin{bmatrix}x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}\\x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}+x_{11}x_{12}\\2x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}+x_{11}x_{12}\end{bmatrix}
\\
\begin{aligned}
{\boldsymbol{F}}_{3\times2}(X)& \left.=\left\lfloor\begin{matrix}{f_{11}(\boldsymbol{X})}&{f_{12}(\boldsymbol{X})}\\{f_{21}(\boldsymbol{X})}&{f_{22}(\boldsymbol{X})}\\{f_{31}(\boldsymbol{X})}&{f_{32}(\boldsymbol{X})}\\\end{matrix}\right.\right\rfloor   \\
&\left.=\left[\begin{array}{ll}x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}&2x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}\\3x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}&4x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}\\5x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}&6x_{11}+x_{12}+x_{21}+x_{22}+x_{31}+x_{32}\end{array}\right.\right]
\end{aligned}
$$

- **向量**变元的**实值标量**函数$f(\boldsymbol{x}),\boldsymbol{x}=[x_1,x_2,\cdots,x_n]^T$

  - **行向量偏导**形式（又称**行偏导向量**形式）

  $$
  \mathrm{D}_{\boldsymbol{x}}f(\boldsymbol{x})=\frac{\partial f(\boldsymbol{x})}{\partial\boldsymbol{x}^T}=\left[\frac{\partial f}{\partial x_1},\frac{\partial f}{\partial x_2},\cdots,\frac{\partial f}{\partial x_n}\right]
  $$

  - **梯度向量**形式（又称**列向量偏导**形式、**列偏导向量**形式）

  $$
  \nabla_xf(\boldsymbol{x})=\frac{\partial f(\boldsymbol{x})}{\partial\boldsymbol{x}}=\left[\frac{\partial f}{\partial x_1},\frac{\partial f}{\partial x_2},\cdots,\frac{\partial f}{\partial x_n}\right]^T
  $$

这两种形式**互为转置**。

- **矩阵**变元的**实值标量**函数$f(\boldsymbol{X}),\boldsymbol{X}_{m\times n}=(x_{ij})_{i=1,j=1}^{m,n}$ 

  先介绍一个符号 $\operatorname{vec}(\boldsymbol X)$ ，作用是将矩阵$\boldsymbol X$**按列堆栈**来向量化，即将$X$ 按列展开为一个列向量。

  - **行向量偏导**形式（又称**行偏导向量**形式）

  $$
  \begin{aligned}
  \mathrm{D}_{\mathrm{vec}\boldsymbol{X}}f(\boldsymbol{X})& =\frac{\partial f(\boldsymbol{X})}{\partial\mathrm{vec}^T(\boldsymbol{X})}  \\
  &=\left[{\frac{\partial f}{\partial x_{11}}},{\frac{\partial f}{\partial x_{21}}},\cdots,{\frac{\partial f}{\partial x_{m1}}},{\frac{\partial f}{\partial x_{12}}},{\frac{\partial f}{\partial x_{22}}},\cdots,{\frac{\partial f}{\partial x_{m2}}},\cdots,{\frac{\partial f}{\partial x_{1n}}},{\frac{\partial f}{\partial x_{2n}}},\cdots,{\frac{\partial f}{\partial x_{mn}}}\right]
  \end{aligned}
  $$

  - $\text{Jacobian}$ 矩阵形式

  $$
  \begin{aligned}
  \operatorname{D}_{X}f(X)& =\frac{\partial f(\boldsymbol{X})}{\partial\boldsymbol{X}_{m\times n}^T}  \\
  &=\begin{bmatrix}\frac{\partial f}{\partial x_{11}}&\frac{\partial f}{\partial x_{21}}&\cdots&\frac{\partial f}{\partial x_{m1}}\\\frac{\partial f}{\partial x_{12}}&\frac{\partial f}{\partial x_{22}}&\cdots&\frac{\partial f}{\partial x_{m2}}\\\vdots&\vdots&\vdots&\vdots\\\frac{\partial f}{\partial x_{1n}}&\frac{\partial f}{\partial x_{2n}}&\cdots&\frac{\partial f}{\partial x_{mn}}\end{bmatrix}_{n\times m}
  \end{aligned}
  $$

  - **梯度向量**形式（又称**列向量偏导**形式、**列偏导向量**形式）

  $$
  \begin{aligned}
  \nabla_{\mathrm{vec}{\boldsymbol{X}}}f(X)& =\frac{\partial f(\boldsymbol{X})}{\partial\mathrm{vec}\boldsymbol{X}}  \\
  &=\left[\frac{\partial f}{\partial x_{11}},\frac{\partial f}{\partial x_{21}},\cdots,\frac{\partial f}{\partial x_{m1}},\frac{\partial f}{\partial x_{12}},\frac{\partial f}{\partial x_{22}},\cdots,\frac{\partial f}{\partial x_{m2}},\cdots,\frac{\partial f}{\partial x_{1n}},\frac{\partial f}{\partial x_{2n}},\cdots,\right.
  \left.\frac{\partial f}{\partial x_{mn}}\right]^{T}
  \end{aligned}
  $$

  - **梯度矩阵**形式

  $$
  \begin{aligned}
  \nabla_{X}f(\boldsymbol{X})& =\frac{\partial f(\boldsymbol{X})}{\partial\boldsymbol{X}_{m\times n}}  \\
  &=\begin{bmatrix}\frac{\partial f}{\partial x_{11}}&\frac{\partial f}{\partial x_{12}}&\cdots&\frac{\partial f}{\partial x_{1n}}\\\frac{\partial f}{\partial x_{21}}&\frac{\partial f}{\partial x_{22}}&\cdots&\frac{\partial f}{\partial x_{2n}}\\\vdots&\vdots&\vdots&\vdots\\\frac{\partial f}{\partial x_{m1}}&\frac{\partial f}{\partial x_{m2}}&\cdots&\frac{\partial f}{\partial x_{mn}}\end{bmatrix}_{m\times n}
  \end{aligned}
  $$

其中，行偏导向量形式和梯度向量形式互为转置，Jacobian矩阵和梯度矩阵互为转置

- **矩阵**变元的**实矩阵**函数 $\boldsymbol{F}(\boldsymbol{X}),\boldsymbol{X}_{m\times n}=(x_{ij})_{i=1,j=1}^{m,n},\boldsymbol{F}_{p\times q}=(f_{ij})_{i=1,j=1}^{p,q}$ 

  - Jacobian矩阵形式

    即先把**矩阵**变元 $X$ 按$vec$**向量化**，转换成**向量**变元：
    $$
    \operatorname{vec}(\boldsymbol{X})=[x_{11},x_{21},\cdots,x_{m1},x_{12},x_{22},\cdots,x_{m2},\cdots,x_{1n},x_{2n},\cdots,x_{mn}]^T
    $$
    再把**实矩阵**函数 $F$ 按 $vec$ **向量化**，转换成**实向量**函数：
    $$
    \begin{aligned}
    &\operatorname{vec}(F(X)) \\
    &=[f_{11}(\boldsymbol{X}),f_{21}(\boldsymbol{X}),\cdots,f_{p1}(\boldsymbol{X}),f_{12}(\boldsymbol{X}),f_{22}(\boldsymbol{X}),\cdots,f_{p2}(\boldsymbol{X}),\cdots,f_{1q}(\boldsymbol{X}),f_{2q}(\boldsymbol{X}) 
    \cdots,f_{pq}(X)]^{T} 
    \end{aligned}
    $$
    Jacobian矩阵是一个 $pq\times mn$ 的矩阵：
    $$
    \begin{aligned}
    \mathrm{D}_{\boldsymbol{X}}\boldsymbol{F}(\boldsymbol{X})&=\frac{\partial\mathrm{vec}_{pq\times1}(\boldsymbol{F}(\boldsymbol{X}))}{\partial\mathrm{vec}_{mn\times1}^T\boldsymbol{X}}
     = \\
    \end{aligned}
    $$
    ![image-20231021185131647](C:\Users\yy\AppData\Roaming\Typora\typora-user-images\image-20231021185131647.png)

