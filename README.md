# OC-ECGView
这个demo是基于CAShapeLayer和UIBezierPath绘制的心电图。在Github中有很多demo都是通过复写
<pre><code>
- (void)drawRect:(CGRect )rect {
	CGContextRef context = UIGraphicsGetCurrentContext();
}
</code></pre>
这个方法来实现的，在这个方法中取得context这个图形上下文然后用这个context来绘制，这种方法在逻辑上是没有问题的，但如果各位同学细心一点，应该会发现，复写了 **- (void)drawRect:(CGRect )rect** 这个方法后，在运行的的时候，当跳转到这个view的时候，运行内存会暴增80M左右，当项目工程过大的时候，本身工程运行内存就很大了，再爆增80M的情况下会有一定几率Crash。

##效果图如下

![示意图](https://github.com/xuxichen/OC-ECGView/raw/master/Demo.gif)

##代码分析
虽然这个是个很简单的demo，但为了让各位同学节省更多的时间，我还是写一下代码分析，让初学者或者急用的人能更快的使用这个demo到自己的项目中去
####背景格子
<pre><code>
//网格分为四种线画成，一种为0.2的横线，一种为0.2的竖线，一种为0.1的横线，一种为0.1的竖线
- (void)drawGrid {

    //  显示区域的宽 和 高
    CGFloat full_height = self.frame.size.height;
    CGFloat full_width = self.frame.size.width;
    //    每一格的宽度
    CGFloat pos_x = 1;
    while (pos_x < full_width) {
        [self drawLineStartPoint:CGPointMake(pos_x, 1) toEndPoint:CGPointMake(pos_x, full_height) withLineWidth:0.2];
        pos_x += _pixelsPerCell;
    }
    
    CGFloat pos_y = 1;
    while (pos_y < full_height) {
        [self drawLineStartPoint:CGPointMake(full_width, pos_y) toEndPoint:CGPointMake(1, pos_y) withLineWidth:0.2];
        pos_y += _pixelsPerCell;
    }
    
    float cell_squar = 0.00;
    
    cell_squar = _pixelsPerCell / 5.00;
    
    pos_x = 1 + cell_squar;
    
    while (pos_x < full_width) {
        [self drawLineStartPoint:CGPointMake(pos_x, 1) toEndPoint:CGPointMake(pos_x, full_height) withLineWidth:0.1];
        pos_x += cell_squar;
    }
    
    pos_y = 1;
    while (pos_y < full_height) {
        [self drawLineStartPoint:CGPointMake(1, pos_y) toEndPoint:CGPointMake(full_width, pos_y) withLineWidth:0.1];
        pos_y += cell_squar;
    }
}
</code></pre>
在上面这段代码中<pre><code></code>[self drawLineStartPoint:CGPointMake(pos_x, 1) toEndPoint:CGPointMake(pos_x, full_height) withLineWidth:0.1];</pre>调用的方法是下面这个方法
<pre><code>
//绘制格子曲线
- (void)drawLineStartPoint:(CGPoint)startPoint toEndPoint:(CGPoint)endPoint withLineWidth:(CGFloat)lineWidth {
    //格子不能用一个bezierpath画，因为会首尾相连，所以要重复创建多个bezierpath对象
    UIBezierPath \*bezierpath = [[UIBezierPath alloc] init];
    [bezierpath moveToPoint:startPoint];
    [self setBezierpathattribute:bezierpath toEndPoint:endPoint withLineWidth:lineWidth];
    //同上
    CAShapeLayer \*shapelayer = [CAShapeLayer layer];
    [self setShapelayerattribute:shapelayer withBezierpath:bezierpath];
}
</code></pre>

而这个方法中设置了bezierpath的相关属性和设置shapelayer相关属性你可以在代码中demo中按住command+左键跳转到这个方法里面查看相关属性的设置
####绘制心电图折线
绘制心电图折线，则是根据传进来的数组来进行处理。然后把这个传进来的数组，按照七个七个的取出来添加到另外一个数组中去，（为什么是七个呢？其实随便多少个都行，只要不是大于数组或者小于零就行，但是为了图像显示的效果最好是六七个，最重要的是：***这个数一定要能整除你输入的数组的个数***）,然后根据这个小的数组，通过计算得到相对应的坐标，通过CAShapeLayer和UIBezierPath把这些坐标点绘制到屏幕上去。
<pre><code>
//绘制折线
- (void)drawCurve {
    //清除掉bezierpath原来的所有坐标点
    [self.bezierpath removeAllPoints];
    /\*  ----------------这一段的数组操作逻辑是我在别人博客中ECGDemo里面的逻辑-------------
        blog.csdn地址：http://blog.csdn.net/iosyangming/article/details/50977395
     对需要绘制的self.lineArray数组的操作，在绘制没有满self的宽度时：
        每次从_ecgArray数组中取出addNumber（最好是能整除你传入的数组的整数，避免数据丢失）个元素添加到self.lineArray数组中去，
     当数组元素个数大于self横屏能容纳的_maxI时：
        把self.lineArray数组中最前面的addNumber个元素除去，
        然后再往self.lineArray数组中添加addNumber个元素
     \*/
    if (self.lineArray.count < \_maxI-addNumber && self.drawNumbers < \_maxI) {
        for (int i=self.drawNumbers; i\<self.drawNumbers+addNumber; i++) {
            [self.lineArray addObject: \_ecgArray[i]];
        }
    }else {
        for (int i=0; i\<addNumber; i++) {
            [self.lineArray removeObjectAtIndex:i];
        }
        for (int i=self.drawNumbers; i\<self.drawNumbers+addNumber; i++) {
            [self.lineArray addObject: \_ecgArray[i]];
        }
    }  
    if (self.drawNumbers \< \_ecgArray.count-addNumber) {
        self.drawNumbers+=addNumber;
    }else {
        self.drawNumbers = 0;
    }
    /\* 
     根据self.lineArray数组中的每个值计算出一个相应的CGPoint，然后把这些坐标点绘制到self上
     \*/
    CGFloat firstpointY = self.height\*0.618 - (CGFloat)[self.lineArray[0] floatValue]\*\_scaleValue;
    CGFloat pointX = 0;
    [self.bezierpath moveToPoint:CGPointMake(pointX, firstpointY)];
    for (int i=1; i\<self.lineArray.count; i++) {
        pointX = pointX + self.pointMartin;
        CGFloat pointY = self.height\*0.618 - (CGFloat)[self.lineArray[i] floatValue]\*\_scaleValue;
        if (pointX \< self.width) {
            [self drawLineLineToPoint:CGPointMake(pointX, pointY) withLineWidth:self.penBrushWidth];
        }else {
            pointX = 0;
        }
    }
    [self.layer addSublayer:self.shapelayer];
}
</code></pre>
这段代码中的相关注释做的比较详细，就不做更多介绍了。