#include "battle_game/core/game_core.h"
#include "battle_game/core/units/lisi_tank.h" 
#include "battle_game/core/units/new_tank.h"
namespace battle_game {

template <class UnitType, class... Args>
void GameCore::AddPrimaryUnitAllocationFunction(Args... args) {
  primary_unit_allocation_functions_.emplace_back([=](uint32_t player_id) {
    return AddUnit<UnitType>(player_id, args...);
  });
}

void GameCore::GeneratePrimaryUnitList() {
  std::unique_ptr<Unit> unit;

#define ADD_SELECTABLE_UNIT(UnitType)                                        \
  unit = std::make_unique<UnitType>(nullptr, 0, 0);                          \
  AddPrimaryUnitAllocationFunction<UnitType>();                              \
  selectable_unit_list_.push_back(unit->UnitName() + std::string(" - By ") + \
                                  unit->Author());

  ADD_SELECTABLE_UNIT(unit::lisi_tank);
  ADD_SELECTABLE_UNIT(unit::new_tank);
  ADD_SELECTABLE_UNIT(unit::Tank);

  unit.reset();
}
}  // namespace battle_game
