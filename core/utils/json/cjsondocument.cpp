

#include "cjsondocument.h"
#include "defaultsettings.h"
#include "jsontagnames.h"
#include "localdirectory.h"
#include "json/jsonexceptions.h"

#include <chrono>
#include <ctime>
#include <filesystem>
#include <fstream>

nlohmann::json CJsonDocument::makeHeader() const
{
    auto now = std::chrono::time_point_cast<std::chrono::seconds>(std::chrono::system_clock::now());
    return {{TagNames::FileSpec::name, "UrzasQuest TextRPG"},
            {TagNames::FileSpec::version, 1},
            {TagNames::FileSpec::fileType, _type},
            {TagNames::FileSpec::dateTime, std::format("{:%Y-%m-%d %H:%M:%S}", now)}

    };
}

CJsonDocument::CJsonDocument(const std::string_view& fileName, const std::string_view& type) :
    CJsonDocument(fileName, LocalDirectory::getLocalDirectoryPath().string(), type)
{
}

CJsonDocument::CJsonDocument(const std::string_view& fileName,
                             const std::string_view& filePath,
                             const std::string_view& type) :
    _type(type)
{
    std::filesystem::path p(filePath);
    p.append(fileName);
    _fileName = p.string();
}

void CJsonDocument::dump() const
{
    dumpAs(_fileName);
}

void CJsonDocument::dumpAs(const std::string_view& fileName) const
{
    try
    {
        std::ofstream f;
        f.open(std::string(fileName), std::ofstream::out | std::ofstream::trunc);
        if (!f.is_open())
        {
            throw Json::CJsonException(std::format("Write file {} failed", fileName));
        }

        nlohmann::json doc;
        doc[TagNames::FileSpec::fileSpec] = makeHeader();
        doc[_type] = _document;
        f << doc.dump(2).c_str() << std::flush;
        f.close();
    }
    catch (const Json::CJsonException& e)
    {
        throw e;
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Json::CJsonException(e);
    }
}

bool CJsonDocument::checkDocType(const nlohmann::json& doc) const
{
    if (!doc.contains(TagNames::FileSpec::fileSpec))
    {
        return false;
    }
    if (!doc[TagNames::FileSpec::fileSpec].contains(TagNames::FileSpec::fileType))
    {
        return false;
    }
    return doc[TagNames::FileSpec::fileSpec][TagNames::FileSpec::fileType].get<std::string>().compare(_type) == 0;
}

bool CJsonDocument::exists() const
{
    return std::filesystem::exists(_fileName);
}

void CJsonDocument::load()
{
    try
    {
        if (!exists())
        {
            throw Json::CJsonException(std::format("File {} does not exist", _fileName));
        }

        std::ifstream f;
        f.open(_fileName);
        if (!f.is_open())
        {
            throw Json::CJsonException(std::format("Read file {} failed", _fileName));
        }
        const auto doc = nlohmann::json::parse(f);

        if (!doc.contains(_type))
        {
            throw Json::CJsonException(std::format("Invalid file, expected type {}", _type));
        }
        _document = doc[_type];

        f.close();
    }
    catch (const Json::CJsonException& e)
    {
        throw e;
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Json::CJsonException(e);
    }
}

const nlohmann::json CJsonDocument::root() const
{
    return _document;
}

int CJsonDocument::get(const std::string_view& key, const int d) const
{
    try
    {
        return getObject(key).get<int>();
    }
    catch (const std::exception&)
    {
        return d;
    }
}

bool CJsonDocument::get(const std::string_view& key, const bool d) const
{
    try
    {
        return getObject(key).get<bool>();
    }
    catch (const std::exception&)
    {
        return d;
    }
}

unsigned int CJsonDocument::get(const std::string_view& key, const unsigned int d) const
{
    try
    {
        return getObject(key).get<unsigned int>();
    }
    catch (const std::exception&)
    {
        return d;
    }
}

std::string CJsonDocument::get(const std::string_view& key, const std::string_view& d) const
{
    try
    {
        return getObject(key).get<std::string>();
    }
    catch (const std::exception&)
    {
        return std::string(d);
    }
}

void CJsonDocument::addObject(const std::string_view& key, const nlohmann::json& object)
{
    _document[key] = object;
}

nlohmann::json CJsonDocument::getObject(const std::string_view& key) const
{
    try
    {
        if (_document.contains(key))
        {
            return _document[key];
        }
    }
    catch (const nlohmann::json::exception& e)
    {
        throw Json::CJsonException(e);
        return {};
    }

    throw Json::CJsonException(std::format("Key not found: {}", key));
    return {};
}