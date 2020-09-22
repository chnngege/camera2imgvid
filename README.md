## run

chmod +x start.sh
./start.sh


## xml file

<?xml version="1.0" encoding="UTF-8" standalone="yes" ?>
<Info num="2"> 
    <camera to="img">                        <!-- 摄像头转为jpg图片的参数 -->
        <time_interval>60</time_interval>    <!-- 采集相邻两张图片的时间间隔(s) -->
        <id>6</id>                           <!-- 上次保存的图片的最大编号 -->
    </camera>
    <camera to="vid">                        <!-- 摄像头转为jpg图片的参数 -->
        <time_interval>10</time_interval>     <!-- 截取相邻两段视频的时间间隔(s) -->
        <id>3</id>                           <!-- 上次保存的视频的最大编号 -->
        <fps>30</fps>                        <!-- 设置保存的视频的帧率 -->
        <fps_enable>0</fps_enable>           <!-- 该参数为0时，所设置的帧率有效；否则将自动设置帧率 -->
        <vid_duration>120</vid_duration>     <!-- 截取视频的时长(s) -->
    </camera>
</Info>


## note

--如果上次截取的视频没有采集完成就关闭，则会导致此视频无效，下次采集编号依然是该编号。主要为了防止出现未达标的视频。
--如果在工程文件夹下没有xml文件，程序会自动生成包含有参数默认值的xml文件

