//
//  UIView+XZWExtension.h
//  XZWMiaowShower
//
//  Created by xuxichen on 16/10/11.
//  Copyright © 2016年 com.xu. All rights reserved.
//
/**
 这个类是基于
 MiaowShow作者Alin
 和
 Erica Sadun, http://ericasadun.com
 iPhone Developer's Cookbook, 3.0 Edition
 BSD License, Use at your own risk
 集合成的一个UIView+XZWExtension。
 我并没有任何多余的功能扩展。
 */
#import <UIKit/UIKit.h>

CGPoint CGRectGetCenter(CGRect rect);
CGRect  CGRectMoveToCenter(CGRect rect, CGPoint center);

@interface UIView (XZWExtension)
/** X */
@property (nonatomic, assign) CGFloat x;

/** Y */
@property (nonatomic, assign) CGFloat y;

/** Width */
@property (nonatomic, assign) CGFloat width;

/** Height */
@property (nonatomic, assign) CGFloat height;

/** size */
@property (nonatomic, assign) CGSize size;

/** centerX */
@property (nonatomic, assign) CGFloat centerX;

/** centerY */
@property (nonatomic, assign) CGFloat centerY;

/** tag */
@property (nonatomic, copy) NSString *tagStr;

- (BOOL)isShowingOnKeyWindow;
/** origin */
@property (nonatomic, assign) CGPoint origin;

@property (readonly) CGPoint bottomLeft;
@property (readonly) CGPoint bottomRight;
@property (readonly) CGPoint topRight;

@property CGFloat top;
@property CGFloat left;

@property CGFloat bottom;
@property CGFloat right;

- (void) moveBy: (CGPoint) delta;
- (void) scaleBy: (CGFloat) scaleFactor;
- (void) fitInSize: (CGSize) aSize;

@end
