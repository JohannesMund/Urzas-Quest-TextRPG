#pragma once

#include <nlohmann/json.hpp>

class CJsonDocument
{
public:
    CJsonDocument(const std::string_view& fileName, const std::string_view& type);
    CJsonDocument(const std::string_view& fileName, const std::string_view& filePath, const std::string_view& type);
    virtual ~CJsonDocument() {};

    virtual void dump() const;

    bool exists() const;

    void load();

    const nlohmann::json root() const;

    int get(const std::string_view& key, const int d) const;
    bool get(const std::string_view& key, const bool d) const;
    unsigned int get(const std::string_view& key, const unsigned int d) const;
    std::string get(const std::string_view& key, const std::string_view& d) const;

    bool get(const nlohmann::json& o, const std::string_view& key, const bool d) const;
    int get(const nlohmann::json& o, const std::string_view& key, const int d) const;
    unsigned int get(const nlohmann::json& o, const std::string_view& key, const unsigned int d) const;
    std::string get(const nlohmann::json& o, const std::string_view& key, const std::string_view& d) const;

protected:
    void addObject(const std::string_view& key, const nlohmann::json& object);

    nlohmann::json getObject(const std::string_view& key) const;
    nlohmann::json getObject(const nlohmann::json& o, const std::string_view& key) const;

    nlohmann::json makeHeader() const;
    void dumpAs(const std::string_view& fileName) const;
    bool checkDocType(const nlohmann::json& doc) const;

    nlohmann::json _document;

private:
    std::string _fileName;
    std::string _type;
};
