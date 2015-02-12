//
//  IMMyself.h
//  IMSDK
//
//  Created by lyc on 14-8-16.
//  Copyright (c) 2014年 lyc. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <UIKit/UIKit.h>

/**
 @enum
 @brief 登录状态
 */
typedef NS_ENUM(NSInteger, IMMyselfLoginStatus) {
    // 未登录
    IMMyselfLoginStatusNone = 0,        // 未登录
    IMMyselfLoginStatusLogining = 1,    // 用户发起登录
    IMMyselfLoginStatusReconnecting = 2,  // 断线重连
    IMMyselfLoginStatusAutoLogining = 4,  // 自动登录
    // 未登录 end
    
    // 已登录
    IMMyselfLoginStatusLogouting = 10,   // 用户发起退出登录
    IMMyselfLoginStatusLogined = 11,    // 已登录
    // 已登录 end
};

/**
 @protocol
 @brief IMMyself登录和文本消息代理
 @discussion IMMyself类中的方法，无论是否带block方法，只要注册接收回调的对象到delegate中，就能监听到回调方法
 */
@protocol IMMyselfDelegate <NSObject>

@optional


#pragma mark - 登录回调

/**
 @method
 @brief 登录成功 的回调方法
 @param autoLogin 是否是自动登录
 */
- (void)didLogin:(BOOL)autoLogin;

/**
 @method
 @brief 登录失败 的回调方法
 @param error 登录失败的错误信息
 */
- (void)loginFailedWithError:(NSString *)error;


#pragma mark - 注销回调

/**
 @method
 @brief 退出登录成功 的回调方法
 @param reason 注销原因
 */
- (void)didLogoutFor:(NSString *)reason;

/**
 @method
 @brief 退出登录失败 的回调方法
 @param error 退出登录失败的错误信息
 */
- (void)logoutFailedWithError:(NSString *)error;

- (void)didLoseConnection;

- (void)didReconnect;

/**
 @method
 @brief 登录状态更新 的回调方法
 @param status
 */
- (void)loginStatusDidUpdateForOldStatus:(IMMyselfLoginStatus)oldStatus newStatus:(IMMyselfLoginStatus)newStatus;


#pragma mark 发送文本消息回调

/**
 @method
 @brief 发送文本消息成功的回调方法
 @param text                  文本消息内容
 @param customUserID          接收方的用户名
 @param timeIntervalSince1970 1970年到客户端发送文本消息时间的秒数
 */
- (void)didSendText:(NSString *)text
             toUser:(NSString *)customUserID
     clientSendTime:(UInt32)timeIntervalSince1970;

/**
 @method
 @brief 发送文本消息失败的回调方法
 @param text                  文本消息内容
 @param customUserID          接收方的用户名
 @param timeIntervalSince1970 1970年到客户端发送文本消息时间的秒数
 @param error                 发送文本消息失败的错误信息
 */
- (void)failedToSendText:(NSString *)text
                  toUser:(NSString *)customUserID
          clientSendTime:(UInt32)timeIntervalSince1970
                   error:(NSString *)error;

/**
 @method
 @brief 接收到文本消息的回调方法
 @param text                  文本消息内容
 @param customUserID          发送方的用户名
 @param timeIntervalSince1970 1970年到服务端发送文本消息时间的秒数
 */
- (void)didReceiveText:(NSString *)text
      fromCustomUserID:(NSString *)customUserID
        serverSendTime:(UInt32)timeIntervalSince1970;


#pragma mark 用户间语音消息
/**
 @method
 @brief 接收到用户间语音消息的回调方法
 @param data                  语音消息数据内容（格式为iLBC）
 @param customUserID          发送方的用户名
 @param timeIntervalSince1970 1970年到服务端发送文本消息时间的秒数
 */
- (void)didReceiveAudioData:(NSData *)data
           fromCustomUserID:(NSString *)customUserID
             serverSendTime:(UInt32)timeIntervalSince1970;

#pragma mark 用户间图片消息
/**
 @method
 @brief 接收到用户间图片消息的回调方法
 @param photo                 收到的图片
 @param customUserID          发送方的用户名
 @param timeIntervalSince1970 1970年到服务端发送文本消息时间的秒数
 */
- (void)didReceivePhoto:(UIImage *)photo
       fromCustomUserID:(NSString *)customUserID
         serverSendTime:(UInt32)timeIntervalSince1970;


#pragma mark 用户间图片消息进度
/**
 @method
 @brief 接收用户间图片消息进度的回调方法
 @param progress              取值范围为 0-1 -- (0, 1]
 @param customUserID          发送方的用户名
 @param timeIntervalSince1970 1970年到服务端发送文本消息时间的秒数
 */
- (void)didReceivePhotoProgress:(CGFloat)progress
               fromCustomUserID:(NSString *)customUserID
                 serverSendTime:(UInt32)timeIntervalSince1970;


#pragma mark 系统消息

/**
 @method
 @brief 接收到系统消息的回调方法
 @param text                  系统消息内容
 @param timeIntervalSince1970 1970年到服务端发送系统消息时间的秒数
 */
- (void)didReceiveSystemText:(NSString *)text serverSendTime:(UInt32)timeIntervalSince1970;

@end


#pragma mark - IMMyself class

/**
 @header IMMyself.h
 @abstract IMSDK的核心类之一，指代当前登录用户对象
 */
@interface IMMyself : NSObject

/**
 @method
 @brief 获取IMMyself单例对象
 */
+ (id)sharedInstance;

/**
 @property
 @brief IMMyself基本代理，包含登录注销和文本消息等
 @discussion 遵循IMMyselfDelegate协议
 */
@property (nonatomic, weak) id<IMMyselfDelegate> delegate;

/**
 @method
 @brief 获取登录用户名
 */
- (NSString *)customUserID;

/**
 @method
 @brief 获取应用标识
 */
- (NSString *)appKey;

/**
 @method
 @brief 判断当前用户是否登录
 */
- (BOOL)isLogined;

/**
 @property
 @brief 获取登录状态
 @discussion 登录状态为IMMyselfLoginStatus的枚举
 */
@property (nonatomic, readonly) IMMyselfLoginStatus loginStatus;

/**
 @method
 @brief 初始化登录信息
 @param customUserID 登录用户名，不能为nil，长度不能超过64个字节
 @param appkey       应用标识，不能为空，开发者需要填写从IMSDK.im官网注册时获取的appkey
 */
- (void)initWithCustomUserID:(NSString *)customUserID appKey:(NSString *)appKey;

/**
 @property
 @brief 是否自动登录
 @discussion 默认为YES，自动登录
 */
@property (nonatomic, assign) BOOL autoLogin;


#pragma mark - 注册

/**
 @method
 @brief 注册接口 （异步方法）
 @param timeoutInterval       注册超时时间
 @param success               注册成功的block回调
 @param failure               注册失败的block回调
 @param error                 注册失败的错误信息
 */
- (UInt32)registerWithTimeoutInterval:(UInt32)timeoutInterval
                              success:(void (^)())success
                              failure:(void (^)(NSString *error))failure;

#pragma mark - 登录

/**
 @method
 @brief 登录接口 （异步方法）
 */
- (UInt32)login;

/**
 @method
 @brief 登录接口 （异步方法）
 @param autoRegister          自动注册
 @param timeoutInterval       登录超时时间
 @param success               登录成功的block回调
 @param autoLogin             是否自动登录
 @param failure               登录失败的block回调
 @param error                 登录失败的错误信息
 */
- (UInt32)loginWithAutoRegister:(BOOL)autoRegister
                timeoutInterval:(UInt32)timeoutInterval
                        success:(void (^)(BOOL autoLogin))success
                        failure:(void (^)(NSString *error))failure;


/**
 @property
 @brief 登录密码
 @discussion 登录密码不能为空，小于16个字节
 */
@property (nonatomic, copy) NSString *password;


#pragma mark - 注销
/**
 @method
 @brief 注销接口 （异步方法）
 @discussion 注销将会自动将IMSDK对应当前用户的deviceToken清空，注销后用户收不到来自IMSDK的推送消息，注销可能需要少许时间
 */
- (UInt32)logout;

/**
 @method
 @brief 退出登录接口 （异步方法）
 @param success               退出登录成功的block回调
 @param failure               退出登录失败的block回调
 @param error                 退出登录失败的错误信息
 */
- (UInt32)logoutOnSuccess:(void (^)())success
                  failure:(void (^)(NSString *error))failure;


#pragma mark - 发送文本消息

/**
 @method
 @brief 发送文本消息 （异步方法）
 @param text                  文本消息内容
 @param customUserID          接收方的用户名
 */
- (UInt32)sendText:(NSString *)text toUser:(NSString *)customUserID;

/**
 @method
 @brief 发送文本消息 （异步方法）
 @param text                  文本消息内容
 @param customUserID          接收方的用户名
 @param success               发送文本消息成功的block回调
 @param failure               发送文本消息失败的block回调
 @param error                 发送文本消息失败的错误信息
 */
- (UInt32)sendText:(NSString *)text
            toUser:(NSString *)customUserID
           success:(void (^)())success
           failure:(void (^)(NSString *error))failure;

/**
 @method
 @brief 向IMSDK服务器发送文本消息 （异步方法，可在IMSDK.im开发者中心查看）
 @param text                  文本消息内容
 @param success               发送文本消息成功的block回调
 @param failure               发送文本消息失败的block回调
 @param error                 发送文本消息失败的错误信息
 */
- (UInt32)sendTextToServer:(NSString *)text
                   success:(void (^)())success
                   failure:(void (^)(NSString *error))failure;

- (BOOL)beginRecordingToUser:(NSString *)customUserID;
- (UInt32)stopRecordingToUser:(NSString *)customUserID
                     needSend:(BOOL)needSend
                      success:(void (^)())success
                     progress:(void(^)(CGFloat progress))progress
                      failure:(void (^)(NSString *error))failure;

- (UInt32)sendPhoto:(UIImage *)photo
             toUser:(NSString *)customUserID
            success:(void (^)())success
           progress:(void(^)(CGFloat progress))progress
            failure:(void (^)(NSString *error))failure;

@end

#define g_pIMMyself [IMMyself sharedInstance]












