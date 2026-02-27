#pragma once
#include "cbasicdjinn.h"
#include "cgenie.h"
#include "cjeannie.h"
#include "nlohmann/json.hpp"
namespace Djinn
{

CBasicDjinn* loadFromJson(const nlohmann::json& json)
{
    CBasicDjinn* djinn;

    if (json[TagNames::Npc::gender] == Core::EGender::eFemale)
    {
        djinn = new CJeannie();
    }
    else
    {
        djinn = new CGenie();
    }
    djinn->load(json);
    return djinn;
}

} // namespace Djinn