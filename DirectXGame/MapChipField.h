#include"Model.h"
#include"WorldTransform.h"
#include<map>

enum class MapChipType {
	kBlank,//空白
	kBlock,//ブロック
};

struct MapChipData {
	std::vector<std::vector<MapChipType>> data;
};

namespace{
	std::map<std::string, MapChipType>mapChipTable = {
	{"0",MapChipType::kBlank},
	{"1",MapChipType::kBlock}
	};
}

class MapChipField {
public:
	void ResetMapChipData();
	void LoadMapChipCsv(const std::string& filePath);
	MapChipType GetMapChipTypeByIndex(uint32_t xIndex,uint32_t yIndex);
	Vector3 GetMapChipPosisionByIndex(uint32_t xIndex,uint32_t yIndex);
	uint32_t GetNumBlockVirtical()const{return kNumBlockVirtical;}
	uint32_t GetNumBlockHorizontal()const{return kNumBlockHorizontal;}

private:
	//1ブロックのサイズ
	static inline const float kBlockWidth=1.0f;
	static inline const float kBlockHeight=1.0f;
	//ブロックの個数
	static inline const uint32_t kNumBlockVirtical=20;
	static inline const uint32_t kNumBlockHorizontal=100;


	MapChipData mapChipData_;



};