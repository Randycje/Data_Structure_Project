#include <iostream>
#include <string>
#include <vector>

struct HousingRecord {
    std::string month;
    std::string town;
    std::string flatType;
    std::string block;
    std::string streetName;
    std::string storeyRange;
    int floorAreaSqm;

    HousingRecord(const std::string& m, const std::string& t, const std::string& f, const std::string& b,
        const std::string& s, const std::string& sr, const std::string& fa)
        : month(m), town(t), flatType(f), block(b), streetName(s), storeyRange(sr), floorAreaSqm(stoi(fa)) {}
};

void APICall();
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* data);