### 1.验证旋转矩阵是正交矩阵:
正交矩阵定义： $AA^T = I$，即$A^{-1} = A^T$，则$A$是正交矩阵，假设 $R$表示：
$$[e_1,~e_2,~e_3] ~~->[e_1^{'},~e_2^{'},~e_3^{'}]$$
另有$$\boldsymbol  a =[a_1,~a_2,~a_3]$$
则有
$$
\begin{equation} 
[e_1,~e_2~,e_3] 
\left[ \begin{matrix} 
a_1 \\
a_2 \\
a_3 
\end{matrix} \right] = [e_1^{'},~e_2^{'},~e_3^{'}] 
\left[ \begin{matrix} 
a_1^{'} \\
a_2^{'} \\
a_3^{'} 
\end{matrix} \right]
\end{equation}$$
$(1)$ 式两边乘
### 3.验证四元数旋转某个点后，结果是一个虚四元数(实部为零),所以仍然对应到一个三维空间点
<!-- $$ \left[
\begin{matrix} 
1 & 0 & 0\\
0 & 1 & 0\\
0 & 0 & 1
\end{matrix} 
\right] $$ -->
### 4.画表总结旋转矩阵、轴角、欧拉角、四元数的转换关系。
### 5.见main.cpp
### 6.见main.cpp，另附Eigen函数
<center>
    <img style="border-radius: 0.3125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" 
    src="https://img-blog.csdnimg.cn/20181029195140657.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2hhbnNoaWhhbzEzMzYyOTU2NTQ=,size_16,color_FFFFFF,t_70">
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">Eigen求解方程组函数注意事项</div>
</center>