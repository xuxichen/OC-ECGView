//
//  ECGView.h
//  心电图
//  
//  Created by 徐子文 on 2017/5/22.
//  Copyright © 2017年 徐子文. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "UIView+XZWExtension.h"
#pragma mark -- 屏幕的宽和高
#define EcgViewScreenWidth [UIScreen mainScreen].bounds.size.width
#define EcgViewScreenHeight [UIScreen mainScreen].bounds.size.height

//不同的手机1mm所代表的逻辑分辨率的点数
#define k1mm (64.100/2)
//6+设计的屏幕根理想情况下是不一样的
#define k6pmm (60.400/2)

static int addNumber = 7;


@interface ECGView : UIView {
    CGFloat _pixelsPerCell; //= 30.00; // 0.2 second per cell
    CGFloat _scaleValue;    //比例因子，根据传入数组的最大值最小值的差与view中你想显示的振幅是多大来求出的比例因子
    CGFloat _pointX;
}

//-------------外部需要传入的心跳数组----------------
@property (nonatomic, copy)NSArray *ecgArray;
//标题
@property (nonatomic, strong)UILabel *titleLabel;
//需要绘制的坐标数组
@property (nonatomic, strong)NSMutableArray *pointArray;
//背景图片名
@property (nonatomic, retain)NSString *BackgroudImage;
//画笔的粗细
@property (nonatomic, assign)CGFloat penBrushWidth;
//画笔数组
@property (nonatomic, strong)NSMutableArray *lineArray;
//画笔
@property (nonatomic, strong)CAShapeLayer *shapelayer;
//画笔颜色
@property (nonatomic, strong)UIColor *drawerColor;
//贝塞尔曲线路径
@property (nonatomic, strong)UIBezierPath *bezierpath;
//定时器
@property (nonatomic, weak) NSTimer *timer;
//drawNumbers：用来取数组的的内容的
@property (nonatomic, assign) int drawNumbers,maxI;
//振幅---范围是0到1，最好是0.6左右，取的是self.iew的高的比例。
@property (nonatomic, assign) CGFloat amplitude;
//间隔，正常是1，如果想让心电图拉长一点可以稍微大一点
@property (nonatomic, assign) CGFloat pointMartin;
//初始化方法
- (instancetype)initWithFrame:(CGRect)frame;

- (void)clearAllEcgPoint;
@end
