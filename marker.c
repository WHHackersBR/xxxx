#include "datatype.h"
#include "config.h"
#include "markdata.h"

// Header for JPEG Encoder

UINT8 *write_markers (UINT8 *output_ptr, UINT32 image_format, UINT32 image_width, UINT32 image_height)
{
	UINT16 i, header_length;
	UINT8 number_of_components;

	// Start of image marker
	*output_ptr++ = 0xFF;
	*output_ptr++ = 0xD8;

	// Quantization table marker
	*output_ptr++ = 0xFF;
	*output_ptr++ = 0xDB;

	// Quantization table length
	*output_ptr++ = 0x00;
	*output_ptr++ = 0x84;

	// Pq, Tq
	*output_ptr++ = 0x00;

	// Lqt table
	for (i=0; i<64; i++)
		*output_ptr++ = Lqt [i];

	// Pq, Tq
	*output_ptr++ = 0x01;

	// Cqt table
	for (i=0; i<64; i++)
		*output_ptr++ = Cqt [i];

	// huffman table(DHT)
	for (i=0; i<210; i++)
	{
		*output_ptr++ = (UINT8) (markerdata [i] >> 8);
		*output_ptr++ = (UINT8) markerdata [i];
	}

	if (image_format == FOUR_ZERO_ZERO)
		number_of_components = 1;
	else
		number_of_components = 3;

	// Frame header(SOF)

	// Start of frame marker
	*output_ptr++ = 0xFF;
	*output_ptr++ = 0xC0;

	header_length = (UINT16) (8 + 3 * number_of_components);

	// Frame header length	
	*output_ptr++ = (UINT8) (header_length >> 8);
	*output_ptr++ = (UINT8) header_length;

	// Precision (P)
	*output_ptr++ = 0x08;

	// image height
	*output_ptr++ = (UINT8) (image_height >> 8);
	*output_ptr++ = (UINT8) image_height;

	// image width
	*output_ptr++ = (UINT8) (image_width >> 8);
	*output_ptr++ = (UINT8) image_width;

	// Nf
	*output_ptr++ = number_of_components;

	if (image_format == FOUR_ZERO_ZERO)
	{
		*output_ptr++ = 0x01;
		*output_ptr++ = 0x11;
		*output_ptr++ = 0x00;
	}
	else
	{
		*output_ptr++ = 0x01;

		if (image_format == FOUR_TWO_ZERO)
			*output_ptr++ = 0x22;
		else if (image_format == FOUR_TWO_TWO)
			*output_ptr++ = 0x21;
		else
			*output_ptr++ = 0x11;

		*output_ptr++ = 0x00;

		*output_ptr++ = 0x02;
		*output_ptr++ = 0x11;
		*output_ptr++ = 0x01;

		*output_ptr++ = 0x03;
		*output_ptr++ = 0x11;
		*output_ptr++ = 0x01;
	}

	// Scan header(SOF)

	// Start of scan marker
	*output_ptr++ = 0xFF;
	*output_ptr++ = 0xDA;

	header_length = (UINT16) (6 + (number_of_components << 1));

	// Scan header length
	*output_ptr++ = (UINT8) (header_length >> 8);
	*output_ptr++ = (UINT8) header_length;

	// Ns
	*output_ptr++ = number_of_components;

	if (image_format == FOUR_ZERO_ZERO)
	{
		*output_ptr++ = 0x01;
		*output_ptr++ = 0x00;
	}
	else
	{
		*output_ptr++ = 0x01;
		*output_ptr++ = 0x00;

		*output_ptr++ = 0x02;
		*output_ptr++ = 0x11;

		*output_ptr++ = 0x03;
		*output_ptr++ = 0x11;
	}

	*output_ptr++ = 0x00;
	*output_ptr++ = 0x3F;
	*output_ptr++ = 0x00;
	return output_ptr;
}
