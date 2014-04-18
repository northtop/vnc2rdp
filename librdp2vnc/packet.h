#ifndef _PACKET_H_
#define _PACKET_H_

#include <stdint.h>

#define R2V_PACKET_READ_UINT8(p, v) \
	do { \
		(v) = *(p)->current++; \
	} while (0)
#define R2V_PACKET_READ_UINT16_BE(p, v) \
	do { \
		(v) = *((uint8_t *)((p)->current++)) << 8; \
		(v) |= *((uint8_t *)((p)->current++)); \
	} while (0)
#define R2V_PACKET_READ_UINT16_LE(p, v) \
	do { \
		(v) = *((uint16_t *)((p)->current)); \
		(p)->current += sizeof(uint16_t); \
	} while (0)
#define R2V_PACKET_READ_UINT32_BE(p, v) \
	do { \
		(v) = (uint32_t) \
			( \
				(*((uint8_t *)((p)->current + 0)) << 0) | \
				(*((uint8_t *)((p)->current + 1)) << 8) | \
				(*((uint8_t *)((p)->current + 2)) << 16) | \
				(*((uint8_t *)((p)->current + 3)) << 24) \
			); \
		(p)->current += sizeof(uint32_t); \
	} while (0)
#define R2V_PACKET_READ_UINT32_LE(p, v) \
	do { \
		(v) = *((uint32_t *)((p)->current)); \
		(p)->current += sizeof(uint32_t); \
	} while (0)

#define R2V_PACKET_WRITE_UINT8(p, v) \
	do { \
		*(p)->current++ = (uint8_t)v; \
	} while (0)
#define R2V_PACKET_WRITE_UINT16_BE(p, v) \
	do { \
		*((p)->current++) = (uint8_t)((v) >> 8); \
		*((p)->current++) = (uint8_t)((v) >> 0); \
	} while (0)
#define R2V_PACKET_WRITE_UINT16_LE(p, v) \
	do { \
		*((uint16_t *)((p)->current)) = (uint16_t)v; \
		(p)->current += sizeof(uint16_t); \
	} while (0)
#define R2V_PACKET_WRITE_UINT32_LE(p, v) \
	do { \
		*((uint32_t *)((p)->current)) = (uint32_t)v; \
		(p)->current += sizeof(uint32_t); \
	} while (0)

#define R2V_PACKET_SEEK(p, n)		(p)->current += (n)
#define R2V_PACKET_SEEK_UINT8(p)	R2V_PACKET_SEEK(p, 1)

typedef struct _packet_t {
	uint16_t max_len;
	uint16_t total_len;
	uint8_t *data;
	uint8_t *current;
} packet_t;

extern packet_t *r2v_packet_init(int max_len);
extern void r2v_packet_reset(packet_t *p);
extern void r2v_packet_destory(packet_t *p);

#endif