/*!
 * mhssvau -- Multi-host Single Software Version Automatic Upgrade
 *            多主机单软件版本自动升级
 * 在GWAC系统中, 相机控制软件、文件服务软件部署在多台主机上. 在不同主机上的软件,
 * 仅在配置文件中存在差异. 更新软件流程繁杂:
 * (1) 编译生成可执行程序
 * (2) 上传程序至主机
 * (3) 登录主机
 * (4) 退出当前驻留程序
 * (5) 拷贝覆盖程序
 * (6) 重新启动程序
 * (7) 检查确认程序正确启动
 * (8) 重复步骤(2)-(7), 直至遍历所有主机
 *
 * mhssvau和mhssvad配合, 自动完成上述工作流程, 以节约人工操作时间, 并避免失误
 *
 * @version 0.1
 * @date   2018年4月11日
 * @author 卢晓猛
 * @email  lxm@nao.cas.cn
 * @note
 * 1) 程序形式为驻留内存. 不重复启动程序, 即内存驻留一份实例
 * 2) 为mhssvad提供TCP/IP网络服务
 * 3) 创建消息队列: msgque_mhssvau. 由本程序做版本控制的程序监测消息队列, 决定是否终止程序.
 *    当被控制程序退出时, 向消息队列写入标志字
 *
 */
#include <string.h>
#include "GLog.h"
#include "globaldef.h"
#include "daemon.h"
#include "ConfigurationParameter.h"

GLog g_Log;

int main(int argc, char **argv) {
	if (argc >= 2) {// 处理命令行参数
		if (strcmp(argv[1], "-d") == 0) {
			ConfigurationParameter param("mhssvau.xml");
			param.Init();
		}
		else g_Log.Write("Usage: mhssvau <-d>\n");
	}
	else {// 常规工作模式
		boost::asio::io_service ios;
		boost::asio::signal_set signals(ios, SIGINT, SIGTERM);  // interrupt signal
		signals.async_wait(boost::bind(&boost::asio::io_service::stop, &ios));

		if (!MakeItDaemon(ios)) return 1;
		if (!isProcSingleton(gPIDPath)) {
			g_Log.Write("%s is already running or failed to access PID file", DAEMON_NAME);
			return 2;
		}

		g_Log.Write("Try to launch %s %s %s as daemon", DAEMON_NAME, DAEMON_VERSION, DAEMON_AUTHORITY);
		// 主程序入口
	//	GeneralControl gc(&ios);
	//	if (gc.StartService()) {
	//		g_Log.Write("Daemon goes running");
	//		ios.run();
	//		gc.StopService();
	//	}
	//	else {
	//		g_Log.Write(LOG_FAULT, NULL, "Fail to launch %s", DAEMON_NAME);
	//	}
		g_Log.Write("Daemon stopped");
	}

	return 0;
}
