#pragma once
#include "croom.h"

/**
 * @brief Register für unser Battlefield Grid
 * @sa cbattlefieldgrid.h
 * Jeder der CBattleFieldGrid mit template aufrufen möchte, muss das hier registrieren.
 */

template class CMapGrid<CRoom*>;
