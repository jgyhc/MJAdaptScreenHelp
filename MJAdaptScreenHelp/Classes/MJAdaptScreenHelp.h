//
//  MJAdaptScreenHelp.h
//  Pods
//
//  Created by manjiwang on 2019/4/4.
//

#ifndef MJAdaptScreenHelp_h
#define MJAdaptScreenHelp_h

#define DH_INLINE static inline
#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

static const CGFloat mj_originWidth_ = 375.f;//iphone6为基准
static const CGFloat mj_originHeight_ = 667.f;

DH_INLINE BOOL mj_isiPhoneX() {
    if (@available(iOS 11.0, *)) {
        UIWindow *keyWindow = [[[UIApplication sharedApplication] delegate] window];
        // 获取底部安全区域高度，iPhone X 竖屏下为 34.0，横屏下为 21.0，其他类型设备都为 0
        CGFloat bottomSafeInset = keyWindow.safeAreaInsets.bottom;
        if (bottomSafeInset == 34.0f || bottomSafeInset == 21.0f) {
            return YES;
        }
    }
    return NO;
}

DH_INLINE CGFloat mj_bottomSpace() {
    if (@available(iOS 11.0, *)) {
        UIWindow *keyWindow = [[[UIApplication sharedApplication] delegate] window];
        // 获取底部安全区域高度，iPhone X 竖屏下为 34.0，横屏下为 21.0，其他类型设备都为 0
        CGFloat bottomSafeInset = keyWindow.safeAreaInsets.bottom;
        return bottomSafeInset;
    }
    return 0;
}

DH_INLINE CGFloat mj_statusBarHeight() {
    CGRect statusBarFrame = [[UIApplication sharedApplication] statusBarFrame];
    return statusBarFrame.size.height;
}

DH_INLINE CGFloat mj_navigationHeight() {
    if (mj_isiPhoneX()) {
        return 88.00;
    }
    return 64.00;
}

//内联函数
DH_INLINE CGFloat mj_hotizontalRatio() {
    return  [UIScreen mainScreen].bounds.size.width / mj_originWidth_;//水平方向上的比率，value当前屏幕的值，return等比例适配后的值
    
}

DH_INLINE CGFloat mj_verticalRatio() {
    return [UIScreen mainScreen].bounds.size.height / mj_originHeight_;//垂直方向上的比率
}
/**
 *  传一个位置大小得到转换后的center
 *
 *  @param frame 位置大小
 *
 *  @return 返回一个点
 */
DH_INLINE CGPoint mj_centerFromFrame(CGRect frame) {
    return CGPointMake(frame.origin.x + frame.size.width / 2, frame.origin.y + frame.size.height / 2);
}

/**
 *  传入大小  和 中心
 *
 *  @param size   大小
 *  @param center 中心位置
 *
 *  @return 返回一个位置大小
 */
DH_INLINE CGRect mj_frameWithSizeAndCenter(CGSize size,CGPoint center) {
    return CGRectMake(center.x - size.width / 2, center.y - size.height / 2, size.width, size.height);
}

DH_INLINE CGPoint mj_flexibleCenter(CGPoint center, BOOL adjustWidth) {//基准屏幕下的center
    if (adjustWidth) {
        CGFloat x = center.x * mj_verticalRatio();
        CGFloat y = center.y * mj_verticalRatio();
        return CGPointMake(x, y);
    }
    CGFloat x = center.x * mj_hotizontalRatio();
    CGFloat y = center.y * mj_verticalRatio();
    return CGPointMake(x, y);//返回一个适配后的center
}

/**
 *  等比例适配size（iphone 4）
 *
 *  @param size        基准屏幕下的size
 *  @param adjustWidth 如果是yes,则返回size的宽高同时乘以高的比率
 *
 *  @return 适配后的size
 */
DH_INLINE CGSize mj_flexibleSize(CGSize size,BOOL adjustWidth) {
    if (adjustWidth) {
        return CGSizeMake(size.width * mj_verticalRatio(), size.height * mj_verticalRatio());
    }
    return CGSizeMake(size.width * mj_hotizontalRatio(), size.height * mj_verticalRatio());
}

DH_INLINE CGRect mj_flexibleFrame(CGRect frame,BOOL adjustWidth) {
    //拿到frame的center,然后对x y等比例缩放
    CGPoint center = mj_centerFromFrame(frame);
    center = mj_flexibleCenter(center, adjustWidth);
    //对宽高等比例缩放，拿到一个CGSize
    CGSize size = mj_flexibleSize(frame.size, adjustWidth);
    //用上面等比例缩放后的center和size组成一个frame返回
    return mj_frameWithSizeAndCenter(size, center);
}

DH_INLINE CGFloat mj_flexibleHeight(CGFloat height) {
    return height * mj_verticalRatio();
}

DH_INLINE CGFloat mj_flexibleWidth(CGFloat width) {
    return width * mj_hotizontalRatio();
}

DH_INLINE CGFloat mj_flexibleReverseHeight(CGFloat height) {
    return height / mj_verticalRatio();
}



#endif /* MJAdaptScreenHelp_h */
