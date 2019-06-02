#pragma once
class AutoBoot
{
public:
	AutoBoot(void);
	~AutoBoot(void);
	BOOL AutoBoot::AutoBootSet();
	BOOL AutoBoot::AutoBootCancel();
	BOOL AutoBoot::IsAutoBoot();
};

