#pragma once
#include <string>

class cConfiguration
{
	enum class cSystemType {
		MRR8001C,
		MRD72
	};
	static cConfiguration* MakeConfiguration(const std::string& strConfigurationType);
	virtual bool RequiresSystemType() { return false; }

	virtual void SetSystemType(const std::string& strSystemType) {}
};

class cSamplePeriodInterface
{
public:
	cSamplePeriodInterface(bool bEnabled = false);

	bool RequiresSamplePeriod() { return m_bHasSamplePeriod; }
	void SetSamplePeriod(int32_t i32SamplePeriod) { m_i32SamplePeriod = i32SamplePeriod; }
private:
	bool m_bHasSamplePeriod;
	int32_t m_i32SamplePeriod;
};

class cSystemTypeInterface
{
public:
	cSystemTypeInterface(bool bEnabled = false);

	bool RequiresSystemType() { return m_bHasSamplePeriod; }
	void SetSystemType(const std::string& strSystemType) { m_strSystemType = strSystemType; }
private:
	bool m_bHasSystemType;
	std::string m_strSystemType;
};

#define CONCAT_HELPER(a,b) a ## b
#define CONCAT(a,b) CONCAT_HELPER(a,b)
#define RNA_CONFIG_ATTRIBUTE(x,y) class CONCAT(c,SamplePeriod){}

RNA_CONFIG_ATTRIBUTE(SamplePeriod, int32_t);

class cDFConfiguration : public cConfiguration
{
};

class cReceiverConfiguration : public cConfiguration
{
};
