/*
 * @file globaldef.h 声明全局唯一参数
 * @version 0.6
 * @date 2017/06/08
 */

#ifndef GLOBALDEF_H_
#define GLOBALDEF_H_

// 软件名称、版本与版权
#define DAEMON_NAME			"mhssvau"
#define DAEMON_VERSION		"v0.1 @ Apr, 2018"
#define DAEMON_AUTHORITY	"© SVOM Group, NAOC"

// 日志文件路径与文件名前缀
const char gLogDir[]    = "/var/log/mhssvau";
const char gLogPrefix[] = "mhssvau_";

// 软件配置文件
const char gConfigPath[] = "/usr/local/etc/mhssvau.xml";

// 文件锁位置
const char gPIDPath[] = "/var/run/mhssvau.pid";

#endif /* GLOBALDEF_H_ */
