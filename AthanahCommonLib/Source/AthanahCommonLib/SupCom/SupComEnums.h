#pragma once

#include <string>
#include <vector>

namespace Athanah {
  enum class TechLevel {
    T0, T1, T2, T3, T4
  };

  enum class ButtonStatus {
    Normal, Hover, Pressed
  };
  enum class SelectableButtonStatus {
    Normal, Hover, Selected, SelectedHover
  };
  enum class Faction {
    Aeon, Cybran, Uef, Seraphim, Undefined
  };
  
  
  enum class SoundLodCutOff {
    UnitMove, Weapon, None, Unknown
  };

  enum class UnitCategory {
    AbilityButton,
    Aeon,
    Air,
    AirStagingPlatform,
    AntiAir,
    AntiMissile,
    AntiNavi,
    AntiSubmarine,
    Artillery,
    Battleship,
    Benign,
    Bomber,
    Bot,
    BuildByCommander,
    BuildByExperimentalSub,
    BuildByLandTier2Factory,
    BuildByLandTier3Factory,
    BuildByQuantumGate,
    BuildByT1Factory,
    BuildByT2Factory,
    BuildByT3Commander,
    BuildByT3Engineer,
    BuildByT3Factory,
    BuildByTier1Engineer,
    BuildByTier2Commander,
    BuildByTier2Engineer,
    CanNotUseAirStaging,
    CanTransportCommander,
    Capture,
    Carrier,
    Civilian,
    Civillian,
    Command,
    Construction,
    ConstructionSortDown,
    CounterIntelligence,
    Cruiser,
    Cybran,
    Defense,
    DefensiveBoat,
    Destroyer,
    DirectFire,
    DragBuild,
    Economic,
    EnergyProduction,
    EnergyStorage,
    Engineer,
    EngineerStation,
    Experimental,
    Factory,
    FavorsWater,
    FerryBeacon,
    FieldEngineer,
    Frigate,
    Gate,
    GroundAttack,
    HighAltitudeAir,
    HighPriorityAir,
    Hover,
    HydroCarbon,
    IndirectFire,
    InsignificantUnit,
    Intelligence,
    Invulnerable,
    Land,
    LightBoat,
    MassExtraction,
    MassFabrication,
    MassProduction,
    MassStorage,
    Mobile,
    MobileSonar,
    NavAL,
    NavalCarrier,
    NeedMobileBuild,
    NoFormation,
    Nuke,
    NukeSubmarine,
    Omni,
    Operation,
    Optics,
    OrbitalSystem,
    OverlayAntiAir,
    OverlayAntiNavi,
    OverlayCounterIntelligence,
    OverlayDefense,
    OverlayDirectFire,
    OverlayIndirectFire,
    OverlayMisc,
    OverlayOmni,
    OverlayRadar,
    OverlaySonar,
    PatrolHelper,
    Pod,
    PodStagingPlatform,
    ProductDL,
    ProductFA,
    ProductSC1,
    Radar,
    RallyPoint,
    Rebuilder,
    Reclaim,
    ReclaimFriendly,
    Reclaimable,
    Repair,
    Satellite,
    Scout,
    Selectable,
    Seraphim,
    Shield,
    ShowAttackReticle,
    ShowQueue,
    Silo,
    Size12,
    Size16,
    Size20,
    Size4,
    Size8,
    Sonar,
    SortConstruction,
    SortDefense,
    SortEconomy,
    SortIntel,
    SortStrategic,
    SpecialHighPriority,
    SpecialLowPriority,
    StationIsPod,
    Strategic,
    Structure,
    SubCommander,
    Submersible,
    T1Submarine,
    T2Submarine,
    TacticalMissilePlatform,
    Tank,
    TargetChaser,
    Tech1,
    Tech2,
    Tech3,
    TeleportBeacon,
    TransportFocus,
    TransportT1,
    TransportT2,
    TransportT3,
    Transportation,
    UEF,
    Unselectable,
    Untargetable,
    VerifyMissleUI,
    VisibleToRecon,
    Wall,


    Unkown
  };

  class EnumConvert {
    public:
      static SoundLodCutOff str2SoundLodCutOff(const std::string&);
      static UnitCategory str2UnitCategory(const std::string&);
      static std::string  unitCategory2niceString(UnitCategory);
      static std::vector<UnitCategory>& allUnitCategories();
  };
}