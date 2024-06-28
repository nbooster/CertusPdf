#pragma once

#include <vector>
#include <cstring>

#include "IByteWriterWithPosition.h"


#define DEFAULT_BUFFER_SIZE 1024 * 1024

#define MAX_BUFFER_SIZE 1024 * 1024 * 1024


class pdfBuffer : public IByteWriterWithPosition
{

public:

	pdfBuffer(const IOBasicTypes::LongBufferSizeType maxSize = DEFAULT_BUFFER_SIZE);

	~pdfBuffer(void){};

	std::size_t maxSize(void) const noexcept;

	std::size_t size(void) const noexcept;

	void copy(IOBasicTypes::Byte* outBuffer, IOBasicTypes::LongBufferSizeType outSize = MAX_BUFFER_SIZE);

	IOBasicTypes::Byte* data(void) noexcept;

	const IOBasicTypes::Byte* data(void) const noexcept;

	void reset(void) noexcept;

	virtual IOBasicTypes::LongBufferSizeType Write(const IOBasicTypes::Byte* inBuffer, IOBasicTypes::LongBufferSizeType inSize) override;

	virtual IOBasicTypes::LongFilePositionType GetCurrentPosition() override;

private:

	std::vector<unsigned char> _buffer;

	std::size_t _position = 0;
};