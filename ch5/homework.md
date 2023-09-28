[TOC]

## slam14讲第五讲课后作业

### 1. 标定一个相机

手边有迈德威视MVSUA145GC mono工业相机，于是用这个标定

先使用相机拍十多张标定板的照片，然后打开matlab，选择Camera Calibrator，选择Add Images将拍好的图片导入。

![image-20230927185616178](https://github.com/SVMawww/GetPhotoURL/blob/main/image-20230927185616178.png?raw=true)

导入完成后，填入黑方块的边长，应该是实际边长。

![image-20230927185547399](https://github.com/SVMawww/GetPhotoURL/blob/main/image-20230927185547399.png?raw=true)

这是matlab中显示自动检测的方块位置

![image-20230927185801659](https://github.com/SVMawww/GetPhotoURL/blob/main/image-20230927185801659.png?raw=true)

开始标定，右侧显示了误差，平均误差在0.14，说明标定效果还是很不错的。

![image-20230927185801659](https://github.com/SVMawww/GetPhotoURL/blob/main/image-20230927185855194.png)

双击工作区的变量可以查看相机内参，重要参数有RadiaDistortion径向畸变，TangentialDistortion切向畸变，IntrinsicMatrix相机内参

![image-20230927190123237](https://github.com/SVMawww/GetPhotoURL/blob/main/image-20230927190123237.png)

### 2.1 叙述相机内参的物理意义。

设 $P=(X,~Y,~Z)^T$ 为像在相机坐标系中的坐标，则
$$
Z
\begin{pmatrix}
u \\
v \\
1
\end{pmatrix}
=
\begin{pmatrix}
f_x & 0 & c_x \\
0 & f_y & c_y \\
0 & 0 & 1
\end{pmatrix}
P
=
KP
$$
$K$ 定义为相机的内参。其物理意义为，能够表示物体在像素坐标系中的坐标和以光心为原点的相机坐标系中的坐标的关系。

### 2.2 如果一个相机的分辨率变为原来的两倍而其他地方不变，那 么它的内参将如何变化?

分辨率变为两倍即，像的像素坐标变为两倍，为使等式成立则
$$
Z
\begin{pmatrix}
2u \\
2v \\
1
\end{pmatrix}
=
\begin{pmatrix}
2f_x & 0 & 2c_x \\
0 & 2f_y & 2c_y \\
0 & 0 & 1
\end{pmatrix}
P
=
KP
$$

### 4. 全局快门和卷帘快门

​		全局曝光时**一次性采集所有**感光单元的信息或为每个感光单元配备一个寄存器暂存电荷，而卷帘曝光则是**分时逐行采集信息**（根据其名“卷帘”就能看出是一排一排 地采集数据）。全局曝光的相机，其所有单元在同一时刻采样，曝光时间和我们设置的曝光时间才是真正一致的。而卷帘曝光的相机第一行首先完成曝光，接着是第二行、第三行...到最后一行完成曝光时，中间大概有数百ns甚至ms级的时间，这就导致整个画面其实不是在同一时间采样的，在面对高速运动的物体是会出现“**果冻效应**”，即图像的不同部分出现倾斜、断层等现象，极大地影响了成像质量和识别的效果。CCD相机一般使用全局快门，而CMOS相机使用全局快门的制造成本很高，需要为每个感光单元配置一个寄存器。

<center>
    <img style="border-radius: 0.3125em;
    box-shadow: 0 2px 4px 0 rgba(34,36,38,.12),0 2px 10px 0 rgba(34,36,38,.08);" 
    src="https://github.com/SVMawww/GetPhotoURL/blob/main/%E5%85%A8%E5%B1%80%E5%BF%AB%E9%97%A8%EF%BC%88%E5%B7%A6%EF%BC%89%E5%8D%B7%E5%B8%98%E5%BF%AB%E9%97%A8%EF%BC%88%E5%8F%B3%EF%BC%89.png" width = "75%" alt=""/>
    <br>
    <div style="color:orange; border-bottom: 1px solid #d9d9d9;
    display: inline-block;
    color: #999;
    padding: 2px;">
      全局快门（左）卷帘快门（右）
  	</div>
</center>


### 5. Kinect RGB-D的标定

1. create a directory for your calibration data files, for example: `mkdir ~/kinect_cal_data; cd ~/kinect_cal_data`
2. Record images for the color camera: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 record color` 
3. Calibrate the intrinsics: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 calibrate color`
4. Record images for the ir camera: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 record ir`
5. Calibrate the intrinsics of the ir camera: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 calibrate ir`
6. Record images on both cameras synchronized: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 record sync`
7. Calibrate the extrinsics: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 calibrate sync`
8. Calibrate the depth measurements: `rosrun kinect2_calibration kinect2_calibration chess5x7x0.03 calibrate depth`
9. Find out the serial number of your kinect2 by looking at the first lines printed out by the kinect2_bridge. The line looks like this: 
   `device serial: 012526541941`
10. Create the calibration results directory in kinect2_bridge/data/$serial: `roscd kinect2_bridge/data; mkdir 012526541941`
11. Copy the following files from your calibration directory (~/kinect_cal_data) into the directory you just created: `calib_color.yaml  calib_depth.yaml  calib_ir.yaml  calib_pose.yaml`
12. Restart the kinect2_bridge and be amazed at the better data.

打印好标定板之后，借助ROS工具标定即可。注意相机放置稳定即可，要标定的参数有RGB彩色图像，IR红外图像，SYNC帧同步以及Depth深度信息。

### 6. 遍历图像

#### 数组遍历法 -- at\<typename>(i,j)

```C++
void colorReduce(Mat& image)
{
     for(int i=0;i<image.rows;i++)
     {
		 for(int j=0;j<image.cols;j++)
		 {
			if(image.channels() == 1)
			{
				//取出灰度图像中i行j列的点
				image.at<uchar>(i,j) = image.at<uchar>(i,j) / 2;			
			}
			else if(image.channels() == 3)
			{
				//取出彩色图像中i行j列第k(0/1/2)通道的颜色点
				image.at<Vec3b>(i,j)[0]=image.at<Vec3b>(i,j)[0] / 2;
				image.at<Vec3b>(i,j)[1]=image.at<Vec3b>(i,j)[1] / 2;
				image.at<Vec3b>(i,j)[2]=image.at<Vec3b>(i,j)[2] / 2;
			}			 
		 }
	 }
}    
```

#### CV指针遍历法

```C++
 void colorReduce(Mat& srcImg,Mat& dstImg)
{
	dstImg = srcImg.clone();
	dstImg.setTo(0);
	int height = srcImg.rows;
	// 将3通道转换为1通道
	int width = srcImg.cols * srcImg.channels();
	for(int k = 0;k < height; k++)
	{
		// 获取第k行的首地址
		const uchar* inData = srcImg.ptr<uchar>(k);
		uchar* outData = dstImg.ptr<uchar>(k);
		//处理每个像素
		for(int i = 0; i < width; i++)
		{
			outData[i] = inData[i] / 2;
		}
	}
}   
```

#### 迭代器遍历法

```C++
//三通道彩色图
void colorReduce(Mat srcImage)
{
	Mat tempImage = srcImage.clone();  
  
    // 初始化原图像迭代器  
    MatConstIterator_<Vec3b> srcIterStart = srcImage.begin<Vec3b>();  
    MatConstIterator_<Vec3b> srcIterEnd = srcImage.end<Vec3b>();  
  
    // 初始化输出图像迭代器  
    MatIterator_<Vec3b> resIterStart = tempImage.begin<Vec3b>();  
    MatIterator_<Vec3b> resIterEnd = tempImage.end<Vec3b>();  
  
    while (srcIterStart != srcIterEnd)   
    {  
        (*resIterStart)[0] = 255 - (*srcIterStart)[0];  
        (*resIterStart)[1] = 255 - (*srcIterStart)[1];  
        (*resIterStart)[2] = 255 - (*srcIterStart)[2];  
  
        srcIterStart++;  
        resIterStart++;  
    } 
}
```

