//
//  PostObjectRestore.h
//  PostObjectRestore
//
//  Created by tencent
//  Copyright (c) 2015年 tencent. All rights reserved.
//
//   ██████╗  ██████╗██╗      ██████╗ ██╗   ██╗██████╗     ████████╗███████╗██████╗ ███╗   ███╗██╗███╗   ██╗ █████╗ ██╗         ██╗      █████╗ ██████╗
//  ██╔═══██╗██╔════╝██║     ██╔═══██╗██║   ██║██╔══██╗    ╚══██╔══╝██╔════╝██╔══██╗████╗ ████║██║████╗  ██║██╔══██╗██║         ██║     ██╔══██╗██╔══██╗
//  ██║   ██║██║     ██║     ██║   ██║██║   ██║██║  ██║       ██║   █████╗  ██████╔╝██╔████╔██║██║██╔██╗ ██║███████║██║         ██║     ███████║██████╔╝
//  ██║▄▄ ██║██║     ██║     ██║   ██║██║   ██║██║  ██║       ██║   ██╔══╝  ██╔══██╗██║╚██╔╝██║██║██║╚██╗██║██╔══██║██║         ██║     ██╔══██║██╔══██╗
//  ╚██████╔╝╚██████╗███████╗╚██████╔╝╚██████╔╝██████╔╝       ██║   ███████╗██║  ██║██║ ╚═╝ ██║██║██║ ╚████║██║  ██║███████╗    ███████╗██║  ██║██████╔╝
//   ╚══▀▀═╝  ╚═════╝╚══════╝ ╚═════╝  ╚═════╝ ╚═════╝        ╚═╝   ╚══════╝╚═╝  ╚═╝╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚══════╝    ╚══════╝╚═╝  ╚═╝╚═════╝
//
//
//                                                                              _             __                 _                _
//                                                                             (_)           / _|               | |              | |
//                                                          ___  ___ _ ____   ___  ___ ___  | |_ ___  _ __    __| | _____   _____| | ___  _ __   ___ _ __ ___
//                                                         / __|/ _ \ '__\ \ / / |/ __/ _ \ |  _/ _ \| '__|  / _` |/ _ \ \ / / _ \ |/ _ \| '_ \ / _ \ '__/ __|
//                                                         \__ \  __/ |   \ V /| | (_|  __/ | || (_) | |    | (_| |  __/\ V /  __/ | (_) | |_) |  __/ |  \__
//                                                         |___/\___|_|    \_/ |_|\___\___| |_| \___/|_|     \__,_|\___| \_/ \___|_|\___/| .__/ \___|_|  |___/
//    ______ ______ ______ ______ ______ ______ ______ ______                                                                            | |
//   |______|______|______|______|______|______|______|______|                                                                           |_|
//



#import <Foundation/Foundation.h>
#import <QCloudCore/QCloudCore.h>
@class QCloudRestoreRequest;
NS_ASSUME_NONNULL_BEGIN
/**
功能描述

POST Object restore 接口可以对一个通过 COS 归档为 archive 类型的对象进行恢复，恢复出的可读取对象是临时的，您可以设置需要保持可读，以及随后删除该临时副本的时间。

您可以用 Days 参数来指定临时对象的过期时间，若超出该时间且期间您没有发起任何复制、延长等操作，该临时对象将被系统自动删除。临时对象仅为 archive 类型对象的副本，被归档的源对象在此期间将始终存在。

恢复模式

通过 COS 的生命周期功能归档为 archive 类型的对象，是不可以被直接读取的，您需要先将归档的对象通过该接口恢复（复制）成一个临时副本，期间 archive 类型的对象仍然存在。您可以选择以下几种恢复速度的模式：

Expedited：当紧急需要恢复数据时，该模式提供了最快的恢复速度，费用较高 。对于小于 256 MB 的文件，在 1~5 分钟的时间内即可获得临时副本。
Standard：默认为该模式，该模式提供了在 3~5 小时后恢复临时副本的能力，通常适用于不太紧急的恢复任务。
Bulk：该模式的恢复成本最低，适用于在一天内提供副本的数据恢复。通常 Bulk 模式可以在 5~12 小时后提供临时副本。
恢复功能说明

查看恢复状态

通过发起 HEAD Object 请求，您可以获得 archive 类型对象的当前恢复状态，状态于 x-cos-restore 头部中提供。

延长临时副本的过期时间

再次发起 POST Object restore，您可以对已经恢复的临时对象进行延期，延期删除的时间将从再次发起请求的时间开始计算。

如果存储桶包含生命周期的配置，则需注意所配置的过期时间，系统将自动执行较短的过期时间配置。例如生命周期配置了所有对象 3 天过期，而恢复对象时指定了 10 天过期，则临时副本将在 3 天后被删除。

恢复错误状态

您无法对于已经在恢复中的对象执行该操作，您将收到如下错误响应：

HTTP/1.1 409 Conflict

您无法对于一个非 archive 类型的对象执行该操作，您将收到如下响应：

HTTP/1.1 405 Method Not Allowed
*/
@interface QCloudPostObjectRestoreRequest : QCloudBizHTTPRequest
/**
    存储桶名
    */
@property (strong, nonatomic) NSString *bucket;
/**
    对象名
    */
@property (strong, nonatomic) NSString *object;
/**
    恢复数据的配置信息
    */
@property (strong, nonatomic) QCloudRestoreRequest *restoreRequest;


@end
NS_ASSUME_NONNULL_END
