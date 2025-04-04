// 非加密型hash,速度极快,支持种子
uint32_t murmur3_32(const char *key, size_t len, uint32_t seed) {
	for(uint32_t i=0; i<len; i++)
	{
		seed ^= (const uint8_t)key[i];
		seed *= 0x5bd1e995;
		seed ^= seed>> 15;
	}
	return seed;
}
