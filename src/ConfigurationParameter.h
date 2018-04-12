/*
 * @file ConfigurationParameter.h 配置文件声明文件
 * @version 0.1
 * @author 卢晓猛
 * @email lxm@nao.cas.cn
 * @note
 * 管理配置参数
 */

#ifndef CONFIGURATIONPARAMETER_H_
#define CONFIGURATIONPARAMETER_H_

#include <string>
using std::string;

class ConfigurationParameter {
public:
	ConfigurationParameter(const string &filepath);
	virtual ~ConfigurationParameter();

public:
	/*!
	 * @brief 初始化配置参数
	 */
	void Init();
	/*!
	 * @brief 加载配置参数
	 */
	void Load();
	/*!
	 * @brief 查看网络服务端口
	 * @return
	 * 网络服务端口
	 */
	uint16_t GetPort();
	/*!
	 * @brief 查看仓库根路径
	 * @return
	 * 仓库根路径
	 */
	string GetRepo();

private:
	// 成员变量
	string filepath_;	//< 配置文件路径
	uint16_t port_;	//< 网络服务端口
	string repo_;	//< 仓库地址
};

#endif /* CONFIGURATIONPARAMETER_H_ */
