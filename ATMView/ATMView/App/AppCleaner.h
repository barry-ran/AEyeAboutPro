#pragma once

class AppCleaner
{
public:
    AppCleaner(void);
    ~AppCleaner(void);

    void clean();				

private:
	/*关闭日志系统*/
    void shutdownLog();	

	/*恢复系统默认的一些设置*/
	void restoreSystemEnv();
};

