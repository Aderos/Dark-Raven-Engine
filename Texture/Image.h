#ifndef _IMAGE_H_
#define _IMAGE_H_

class Image
{
public:
	virtual unsigned int GetLevel() = 0;
	virtual unsigned int GetInternalFormat() = 0;
	virtual unsigned int GetWidth() = 0;
	virtual unsigned int GetHeight() = 0;
	virtual unsigned int GetBorder() = 0;
	virtual unsigned int GetFormat() = 0;
	virtual unsigned int GetType() = 0;
	virtual unsigned char* GetData() = 0;

	virtual void Load(const char*) = 0;

	virtual void Release() = 0;
	virtual void Shutdown() = 0;

};

#endif