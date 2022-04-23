#include "SupComEnums.h"

#include <map>
#include <stdexcept>

namespace Athanah {
  UnitCategory str2UnitCategory(const std::string& input) {
    static std::map<std::string, UnitCategory> categoryMap;
    if (categoryMap.size() == 0) {
      categoryMap["PRODUCTDL"                   ] = UnitCategory::ProductDL;
      categoryMap["PRODUCTSC1"                  ] = UnitCategory::ProductSC1;
      categoryMap["OPERATION"                   ] = UnitCategory::Operation;
      categoryMap["SELECTABLE"                  ] = UnitCategory::Selectable;
      categoryMap["AEON"                        ] = UnitCategory::Aeon;
      categoryMap["UEF"                         ] = UnitCategory::UEF;
      categoryMap["CYBRAN"                      ] = UnitCategory::Cybran;
      categoryMap["CIVILIAN"                    ] = UnitCategory::Civilian;
      categoryMap["MOBILE"                      ] = UnitCategory::Mobile;
      categoryMap["HIGHPRIAIR"                  ] = UnitCategory::HighPriorityAir;
      categoryMap["AIR"                         ] = UnitCategory::Air;
      categoryMap["HIGHALTAIR"                  ] = UnitCategory::HighAltitudeAir;
      categoryMap["LAND"                        ] = UnitCategory::Land;
      categoryMap["HOVER"                       ] = UnitCategory::Hover;
      categoryMap["TECH1"                       ] = UnitCategory::Tech1;
      categoryMap["TECH2"                       ] = UnitCategory::Tech2;
      categoryMap["TECH3"                       ] = UnitCategory::Tech3;
      categoryMap["EXPERIMENTAL"                ] = UnitCategory::Experimental;
      categoryMap["BOMBER"                      ] = UnitCategory::Bomber;
      categoryMap["TANK"                        ] = UnitCategory::Tank;
      categoryMap["ANTIAIR"                     ] = UnitCategory::AntiAir;
      categoryMap["BOT"                         ] = UnitCategory::Bot;
      categoryMap["INTELLIGENCE"                ] = UnitCategory::Intelligence;
      categoryMap["SCOUT"                       ] = UnitCategory::Scout;
      categoryMap["TRANSPORTATION"              ] = UnitCategory::Transportation;
      categoryMap["ANTINAVY"                    ] = UnitCategory::AntiNavi;
      categoryMap["RADAR"                       ] = UnitCategory::Radar;
      categoryMap["AIRSTAGINGPLATFORM"          ] = UnitCategory::AirStagingPlatform;
      categoryMap["CARRIER"                     ] = UnitCategory::Carrier;
      categoryMap["FACTORY"                     ] = UnitCategory::Factory;
      categoryMap["DIRECTFIRE"                  ] = UnitCategory::DirectFire;
      categoryMap["GROUNDATTACK"                ] = UnitCategory::GroundAttack;
      categoryMap["VISIBLETORECON"              ] = UnitCategory::VisibleToRecon;
      categoryMap["RECLAIMABLE"                 ] = UnitCategory::Reclaimable; 
      categoryMap["TRANSPORTATION"              ] = UnitCategory::Transportation;
      categoryMap["SHOWATTACKRETICLE"           ] = UnitCategory::ShowAttackReticle;
      categoryMap["CANTRANSPORTCOMMANDER"       ] = UnitCategory::CanTransportCommander;
      categoryMap["TRANSPORTFOCUS"              ] = UnitCategory::TransportFocus;
      categoryMap["TRANSPORTBUILTBYTIER1FACTORY"] = UnitCategory::TransportT1;
      categoryMap["TRANSPORTBUILTBYTIER2FACTORY"] = UnitCategory::TransportT2;
      categoryMap["TRANSPORTBUILTBYTIER3FACTORY"] = UnitCategory::TransportT3;
      categoryMap["BUILTBYTIER1FACTORY"         ] = UnitCategory::BuildByT1Factory;
      categoryMap["BUILTBYTIER2FACTORY"         ] = UnitCategory::BuildByT2Factory;
      categoryMap["BUILTBYTIER3FACTORY"         ] = UnitCategory::BuildByT3Factory;
      categoryMap["BUILTBYTIER3COMMANDER"       ] = UnitCategory::BuildByT3Commander;
      categoryMap["BUILTBYTIER3ENGINEER"        ] = UnitCategory::BuildByT3Engineer;
      categoryMap["NEEDMOBILEBUILD"             ] = UnitCategory::NeedMobileBuild;
      categoryMap["DRAGBUILD"                   ] = UnitCategory::DragBuild;
      categoryMap["OVERLAYDIRECTFIRE"           ] = UnitCategory::OverlayDirectFire;
      categoryMap["OVERLAYANTIAIR"              ] = UnitCategory::OverlayAntiAir;
      categoryMap["OVERLAYRADAR"                ] = UnitCategory::OverlayRadar;
      categoryMap["OVERLAYSONAR"                ] = UnitCategory::OverlaySonar;
      categoryMap["OVERLAYOMNI"                 ] = UnitCategory::OverlayOmni;
      categoryMap["TARGETCHASER"                ] = UnitCategory::TargetChaser;
      categoryMap["SHOWQUEUE"                   ] = UnitCategory::ShowQueue;
      categoryMap["OVERLAYANTINAVY"             ] = UnitCategory::OverlayAntiNavi;
      categoryMap["OVERLAYMISC"                 ] = UnitCategory::OverlayMisc;
      categoryMap["BUILTBYTIER1ENGINEER"        ] = UnitCategory::BuildByTier1Engineer;
      categoryMap["BUILTBYTIER2ENGINEER"        ] = UnitCategory::BuildByTier2Engineer;
      categoryMap["BUILTBYCOMMANDER"            ] = UnitCategory::BuildByCommander;
      categoryMap["BUILTBYTIER2COMMANDER"       ] = UnitCategory::BuildByTier2Commander;
      categoryMap["STRUCTURE"                   ] = UnitCategory::Structure;
      categoryMap["HYDROCARBON"                 ] = UnitCategory::HydroCarbon;
      categoryMap["CONSTRUCTION"                ] = UnitCategory::Construction;
      categoryMap["RALLYPOINT"                  ] = UnitCategory::RallyPoint;
      categoryMap["SIZE4"                       ] = UnitCategory::Size4;
      categoryMap["SIZE16"                      ] = UnitCategory::Size16;
      categoryMap["SIZE20"                      ] = UnitCategory::Size20;
      categoryMap["SORTCONSTRUCTION"            ] = UnitCategory::SortConstruction;
      categoryMap["NAVAL"                       ] = UnitCategory::NavAL;
      categoryMap["CONSTRUCTIONSORTDOWN"        ] = UnitCategory::ConstructionSortDown;
      categoryMap["GATE"                        ] = UnitCategory::Gate;
      categoryMap["SORTSTRATEGIC"               ] = UnitCategory::SortStrategic;
      categoryMap["ECONOMIC"                    ] = UnitCategory::Economic;
      categoryMap["ENERGYPRODUCTION"            ] = UnitCategory::EnergyProduction;
      categoryMap["SORTECONOMY"                 ] = UnitCategory::SortEconomy;
      categoryMap["SIZE12"                      ] = UnitCategory::Size12;
      categoryMap["MASSPRODUCTION"              ] = UnitCategory::MassProduction;
      categoryMap["MASSEXTRACTION"              ] = UnitCategory::MassExtraction;
      categoryMap["MASSFABRICATION"             ] = UnitCategory::MassFabrication;
      categoryMap["ENERGYSTORAGE"               ] = UnitCategory::EnergyStorage;
      categoryMap["MASSSTORAGE"                 ] = UnitCategory::MassStorage;
      categoryMap["DEFENSE"                     ] = UnitCategory::Defense;
      categoryMap["SORTDEFENSE"                 ] = UnitCategory::SortDefense;
      categoryMap["STRATEGIC"                   ] = UnitCategory::Strategic;
      categoryMap["INDIRECTFIRE"                ] = UnitCategory::IndirectFire;
      categoryMap["TACTICALMISSILEPLATFORM"     ] = UnitCategory::TacticalMissilePlatform;
      categoryMap["SILO"                        ] = UnitCategory::Silo;
      categoryMap["OVERLAYINDIRECTFIRE"         ] = UnitCategory::OverlayIndirectFire;
      categoryMap["ARTILLERY"                   ] = UnitCategory::Artillery;
      categoryMap["NUKE"                        ] = UnitCategory::Nuke;
      categoryMap["SORTINTEL"                   ] = UnitCategory::SortIntel;
      categoryMap["SONAR"                       ] = UnitCategory::Sonar;
      categoryMap["OMNI"                        ] = UnitCategory::Omni;
      categoryMap["ANTIMISSILE"                 ] = UnitCategory::AntiMissile;
      categoryMap["OVERLAYDEFENSE"              ] = UnitCategory::OverlayDefense;
      categoryMap["SHIELD"                      ] = UnitCategory::Shield;
      categoryMap["COUNTERINTELLIGENCE"         ] = UnitCategory::CounterIntelligence;
      categoryMap["OVERLAYCOUNTERINTEL"         ] = UnitCategory::OverlayCounterIntelligence;
      categoryMap["SIZE8"                       ] = UnitCategory::Size8;
      categoryMap["WALL"                        ] = UnitCategory::Wall;
      categoryMap["BENIGN"                      ] = UnitCategory::Benign;
      categoryMap["UNTARGETABLE"                ] = UnitCategory::Untargetable;
      categoryMap["FERRYBEACON"                 ] = UnitCategory::FerryBeacon;
      categoryMap["TELEPORTBEACON"              ] = UnitCategory::TeleportBeacon;
      categoryMap["COMMAND"                     ] = UnitCategory::Command;
      categoryMap["REPAIR"                      ] = UnitCategory::Repair;
      categoryMap["ENGINEER"                    ] = UnitCategory::Engineer;
      categoryMap["RECLAIM"                     ] = UnitCategory::Reclaim;
      categoryMap["CAPTURE"                     ] = UnitCategory::Capture;
      categoryMap["PATROLHELPER"                ] = UnitCategory::PatrolHelper;
      categoryMap["REBUILDER"                   ] = UnitCategory::Rebuilder;
      categoryMap["BUILTBYQUANTUMGATE"          ] = UnitCategory::BuildByQuantumGate;
      categoryMap["SUBCOMMANDER"                ] = UnitCategory::SubCommander;
      categoryMap["BUILTBYEXPERIMENTALSUB"      ] = UnitCategory::BuildByExperimentalSub;
      categoryMap["LIGHTBOAT"                   ] = UnitCategory::LightBoat;
      categoryMap["FRIGATE"                     ] = UnitCategory::Frigate;
      categoryMap["ANTISUB"                     ] = UnitCategory::AntiSubmarine;
      categoryMap["DESTROYER"                   ] = UnitCategory::Destroyer;
      categoryMap["CRUISER"                     ] = UnitCategory::Cruiser;
      categoryMap["SUBMERSIBLE"                 ] = UnitCategory::Submersible;
      categoryMap["T1SUBMARINE"                 ] = UnitCategory::T1Submarine;
      categoryMap["BATTLESHIP"                  ] = UnitCategory::Battleship;
      categoryMap["NAVALCARRIER"                ] = UnitCategory::NavalCarrier;
      categoryMap["NUKESUB"                     ] = UnitCategory::NukeSubmarine;
      categoryMap["MOBILESONAR"                 ] = UnitCategory::MobileSonar;
      categoryMap["POD"                         ] = UnitCategory::Pod;
      categoryMap["SPECIALHIGHPRI"              ] = UnitCategory::SpecialHighPriority;
      categoryMap["SPECIALLOWPRI"               ] = UnitCategory::SpecialLowPriority;
      categoryMap["PODSTAGINGPLATFORM"          ] = UnitCategory::PodStagingPlatform;
      categoryMap["VERIFYMISSILEUI"             ] = UnitCategory::VerifyMissleUI;
      categoryMap["NOFORMATION"                 ] = UnitCategory::NoFormation;
      categoryMap["INSIGNIFICANTUNIT"           ] = UnitCategory::InsignificantUnit;
      categoryMap["Cybran"                      ] = UnitCategory::Cybran;
      categoryMap["FAVORSWATER"                 ] = UnitCategory::FavorsWater;
      categoryMap["PRODUCTFA"                   ] = UnitCategory::ProductFA;
      categoryMap["OPTICS"                      ] = UnitCategory::Optics;
      categoryMap["ABILITYBUTTON"               ] = UnitCategory::AbilityButton;
      categoryMap["T2SUBMARINE"                 ] = UnitCategory::T2Submarine;
      categoryMap["SATELLITE"                   ] = UnitCategory::Satellite;
      categoryMap["STATIONASSISTPOD"            ] = UnitCategory::StationIsPod;
      categoryMap["ENGINEERSTATION"             ] = UnitCategory::EngineerStation;
      categoryMap["ORBITALSYSTEM"               ] = UnitCategory::OrbitalSystem;
      categoryMap["BUILTBYLANDTIER2FACTORY"     ] = UnitCategory::BuildByLandTier2Factory;
      categoryMap["BUILTBYLANDTIER3FACTORY"     ] = UnitCategory::BuildByLandTier3Factory;
      categoryMap["FIELDENGINEER"               ] = UnitCategory::FieldEngineer;
      categoryMap["DEFENSIVEBOAT"               ] = UnitCategory::DefensiveBoat;
      categoryMap["SERAPHIM"                    ] = UnitCategory::Seraphim;
      categoryMap["INVULNERABLE"                ] = UnitCategory::Invulnerable;
      categoryMap["CIVILLIAN"                   ] = UnitCategory::Civillian;
      categoryMap["UNSELECTABLE"                ] = UnitCategory::Unselectable;
      categoryMap["CANNOTUSEAIRSTAGING"         ] = UnitCategory::CanNotUseAirStaging;
      categoryMap["RECLAIMFRIENDLY"             ] = UnitCategory::ReclaimFriendly;
      
    }
    if (categoryMap.count(input))
      return categoryMap[input];
    throw std::runtime_error("Category not found");
  }

  std::string unitCategory2niceString(UnitCategory input) {
    static std::map<UnitCategory,std::string> categoryMap;
    if (categoryMap.size() == 0) {
      categoryMap[UnitCategory::ProductDL                 ] = "ProductDL";
      categoryMap[UnitCategory::ProductSC1                ] = "ProductSC1";
      categoryMap[UnitCategory::Operation                 ] = "Operation";
      categoryMap[UnitCategory::Selectable                ] = "Selectable";
      categoryMap[UnitCategory::Aeon                      ] = "Aeon";
      categoryMap[UnitCategory::UEF                       ] = "UEF";
      categoryMap[UnitCategory::Cybran                    ] = "Cybran";
      categoryMap[UnitCategory::Civilian                  ] = "Civilian";
      categoryMap[UnitCategory::Mobile                    ] = "Mobile";
      categoryMap[UnitCategory::HighPriorityAir           ] = "HighPriorityAir";
      categoryMap[UnitCategory::Air                       ] = "Air";
      categoryMap[UnitCategory::HighAltitudeAir           ] = "HighAltitudeAir";
      categoryMap[UnitCategory::Land                      ] = "Land";
      categoryMap[UnitCategory::Hover                     ] = "Hover";
      categoryMap[UnitCategory::Tech1                     ] = "Tech1";
      categoryMap[UnitCategory::Tech2                     ] = "Tech2";
      categoryMap[UnitCategory::Tech3                     ] = "Tech3";
      categoryMap[UnitCategory::Experimental              ] = "Experimental";
      categoryMap[UnitCategory::Bomber                    ] = "Bomber";
      categoryMap[UnitCategory::Tank                      ] = "Tank";
      categoryMap[UnitCategory::AntiAir                   ] = "AntiAir";
      categoryMap[UnitCategory::Bot                       ] = "Bot";
      categoryMap[UnitCategory::Intelligence              ] = "Intelligence";
      categoryMap[UnitCategory::Scout                     ] = "Scout";
      categoryMap[UnitCategory::Transportation            ] = "Transportation";
      categoryMap[UnitCategory::AntiNavi                  ] = "AntiNavi";
      categoryMap[UnitCategory::Radar                     ] = "Radar";
      categoryMap[UnitCategory::AirStagingPlatform        ] = "AirStagingPlatform";
      categoryMap[UnitCategory::Carrier                   ] = "Carrier";
      categoryMap[UnitCategory::Factory                   ] = "Factory";
      categoryMap[UnitCategory::DirectFire                ] = "DirectFire";
      categoryMap[UnitCategory::GroundAttack              ] = "GroundAttack";
      categoryMap[UnitCategory::VisibleToRecon            ] = "VisibleToRecon";
      categoryMap[UnitCategory::Reclaimable               ] = "Reclaimable";
      categoryMap[UnitCategory::Transportation            ] = "Transportation";
      categoryMap[UnitCategory::ShowAttackReticle         ] = "ShowAttackReticle";
      categoryMap[UnitCategory::CanTransportCommander     ] = "CanTransportCommander";
      categoryMap[UnitCategory::TransportFocus            ] = "TransportFocus";
      categoryMap[UnitCategory::TransportT1               ] = "TransportT1";
      categoryMap[UnitCategory::TransportT2               ] = "TransportT2";
      categoryMap[UnitCategory::TransportT3               ] = "TransportT3";
      categoryMap[UnitCategory::BuildByT1Factory          ] = "BuildByT1Factory";
      categoryMap[UnitCategory::BuildByT2Factory          ] = "BuildByT2Factory";
      categoryMap[UnitCategory::BuildByT3Factory          ] = "BuildByT3Factory";
      categoryMap[UnitCategory::BuildByT3Commander        ] = "BuildByT3Commander";
      categoryMap[UnitCategory::BuildByT3Engineer         ] = "BuildByT3Engineer";
      categoryMap[UnitCategory::NeedMobileBuild           ] = "NeedMobileBuild";
      categoryMap[UnitCategory::DragBuild                 ] = "DragBuild";
      categoryMap[UnitCategory::OverlayDirectFire         ] = "OverlayDirectFire";
      categoryMap[UnitCategory::OverlayAntiAir            ] = "OverlayAntiAir";
      categoryMap[UnitCategory::OverlayRadar              ] = "OverlayRadar";
      categoryMap[UnitCategory::OverlaySonar              ] = "OverlaySonar";
      categoryMap[UnitCategory::OverlayOmni               ] = "OverlayOmni";
      categoryMap[UnitCategory::TargetChaser              ] = "TargetChaser";
      categoryMap[UnitCategory::ShowQueue                 ] = "ShowQueue";
      categoryMap[UnitCategory::OverlayAntiNavi           ] = "OverlayAntiNavi";
      categoryMap[UnitCategory::OverlayMisc               ] = "OverlayMisc";
      categoryMap[UnitCategory::BuildByTier1Engineer      ] = "BuildByTier1Engineer";
      categoryMap[UnitCategory::BuildByTier2Engineer      ] = "BuildByTier2Engineer";
      categoryMap[UnitCategory::BuildByCommander          ] = "BuildByCommander";
      categoryMap[UnitCategory::BuildByTier2Commander     ] = "BuildByTier2Commander";
      categoryMap[UnitCategory::Structure                 ] = "Structure";
      categoryMap[UnitCategory::HydroCarbon               ] = "HydroCarbon";
      categoryMap[UnitCategory::Construction              ] = "Construction";
      categoryMap[UnitCategory::RallyPoint                ] = "RallyPoint";
      categoryMap[UnitCategory::Size4                     ] = "Size4";
      categoryMap[UnitCategory::Size16                    ] = "Size16";
      categoryMap[UnitCategory::Size20                    ] = "Size20";
      categoryMap[UnitCategory::SortConstruction          ] = "SortConstruction";
      categoryMap[UnitCategory::NavAL                     ] = "NavAL";
      categoryMap[UnitCategory::ConstructionSortDown      ] = "ConstructionSortDown";
      categoryMap[UnitCategory::Gate                      ] = "Gate";
      categoryMap[UnitCategory::SortStrategic             ] = "SortStrategic";
      categoryMap[UnitCategory::Economic                  ] = "Economic";
      categoryMap[UnitCategory::EnergyProduction          ] = "EnergyProduction";
      categoryMap[UnitCategory::SortEconomy               ] = "SortEconomy";
      categoryMap[UnitCategory::Size12                    ] = "Size12";
      categoryMap[UnitCategory::MassProduction            ] = "MassProduction";
      categoryMap[UnitCategory::MassExtraction            ] = "MassExtraction";
      categoryMap[UnitCategory::MassFabrication           ] = "MassFabrication";
      categoryMap[UnitCategory::EnergyStorage             ] = "EnergyStorage";
      categoryMap[UnitCategory::MassStorage               ] = "MassStorage";
      categoryMap[UnitCategory::Defense                   ] = "Defense";
      categoryMap[UnitCategory::SortDefense               ] = "SortDefense";
      categoryMap[UnitCategory::Strategic                 ] = "Strategic";
      categoryMap[UnitCategory::IndirectFire              ] = "IndirectFire";
      categoryMap[UnitCategory::TacticalMissilePlatform   ] = "TacticalMissilePlatform";
      categoryMap[UnitCategory::Silo                      ] = "Silo";
      categoryMap[UnitCategory::OverlayIndirectFire       ] = "OverlayIndirectFire";
      categoryMap[UnitCategory::Artillery                 ] = "Artillery";
      categoryMap[UnitCategory::Nuke                      ] = "Nuke";
      categoryMap[UnitCategory::SortIntel                 ] = "SortIntel";
      categoryMap[UnitCategory::Sonar                     ] = "Sonar";
      categoryMap[UnitCategory::Omni                      ] = "Omni";
      categoryMap[UnitCategory::AntiMissile               ] = "AntiMissile";
      categoryMap[UnitCategory::OverlayDefense            ] = "OverlayDefense";
      categoryMap[UnitCategory::Shield                    ] = "Shield";
      categoryMap[UnitCategory::CounterIntelligence       ] = "CounterIntelligence";
      categoryMap[UnitCategory::OverlayCounterIntelligence] = "OverlayCounterIntelligence";
      categoryMap[UnitCategory::Size8                     ] = "Size8";
      categoryMap[UnitCategory::Wall                      ] = "Wall";
      categoryMap[UnitCategory::Benign                    ] = "Benign";
      categoryMap[UnitCategory::Untargetable              ] = "Untargetable";
      categoryMap[UnitCategory::FerryBeacon               ] = "FerryBeacon";
      categoryMap[UnitCategory::TeleportBeacon            ] = "TeleportBeacon";
      categoryMap[UnitCategory::Command                   ] = "Command";
      categoryMap[UnitCategory::Repair                    ] = "Repair";
      categoryMap[UnitCategory::Engineer                  ] = "Engineer";
      categoryMap[UnitCategory::Reclaim                   ] = "Reclaim";
      categoryMap[UnitCategory::Capture                   ] = "Capture";
      categoryMap[UnitCategory::PatrolHelper              ] = "PatrolHelper";
      categoryMap[UnitCategory::Rebuilder                 ] = "Rebuilder";
      categoryMap[UnitCategory::BuildByQuantumGate        ] = "BuildByQuantumGate";
      categoryMap[UnitCategory::SubCommander              ] = "SubCommander";
      categoryMap[UnitCategory::BuildByExperimentalSub    ] = "BuildByExperimentalSub";
      categoryMap[UnitCategory::LightBoat                 ] = "LightBoat";
      categoryMap[UnitCategory::Frigate                   ] = "Frigate";
      categoryMap[UnitCategory::AntiSubmarine             ] = "AntiSubmarine";
      categoryMap[UnitCategory::Destroyer                 ] = "Destroyer";
      categoryMap[UnitCategory::Cruiser                   ] = "Cruiser";
      categoryMap[UnitCategory::Submersible               ] = "Submersible";
      categoryMap[UnitCategory::T1Submarine               ] = "T1Submarine";
      categoryMap[UnitCategory::Battleship                ] = "Battleship";
      categoryMap[UnitCategory::NavalCarrier              ] = "NavalCarrier";
      categoryMap[UnitCategory::NukeSubmarine             ] = "NukeSubmarine";
      categoryMap[UnitCategory::MobileSonar               ] = "MobileSonar";
      categoryMap[UnitCategory::Pod                       ] = "Pod";
      categoryMap[UnitCategory::SpecialHighPriority       ] = "SpecialHighPriority";
      categoryMap[UnitCategory::SpecialLowPriority        ] = "SpecialLowPriority";
      categoryMap[UnitCategory::PodStagingPlatform        ] = "PodStagingPlatform";
      categoryMap[UnitCategory::VerifyMissleUI            ] = "VerifyMissleUI";
      categoryMap[UnitCategory::NoFormation               ] = "NoFormation";
      categoryMap[UnitCategory::InsignificantUnit         ] = "InsignificantUnit";
      categoryMap[UnitCategory::Cybran                    ] = "Cybran";
      categoryMap[UnitCategory::FavorsWater               ] = "FavorsWater";
      categoryMap[UnitCategory::ProductFA                 ] = "ProductFA";
      categoryMap[UnitCategory::Optics                    ] = "Optics";
      categoryMap[UnitCategory::AbilityButton             ] = "AbilityButton";
      categoryMap[UnitCategory::T2Submarine               ] = "T2Submarine";
      categoryMap[UnitCategory::Satellite                 ] = "Satellite";
      categoryMap[UnitCategory::StationIsPod              ] = "StationIsPod";
      categoryMap[UnitCategory::EngineerStation           ] = "EngineerStation";
      categoryMap[UnitCategory::OrbitalSystem             ] = "OrbitalSystem";
      categoryMap[UnitCategory::BuildByLandTier2Factory   ] = "BuildByLandTier2Factory";
      categoryMap[UnitCategory::BuildByLandTier3Factory   ] = "BuildByLandTier3Factory";
      categoryMap[UnitCategory::FieldEngineer             ] = "FieldEngineer";
      categoryMap[UnitCategory::DefensiveBoat             ] = "DefensiveBoat";
      categoryMap[UnitCategory::Seraphim                  ] = "Seraphim";
      categoryMap[UnitCategory::Invulnerable              ] = "Invulnerable";
      categoryMap[UnitCategory::Civillian                 ] = "Civillian";
      categoryMap[UnitCategory::Unselectable              ] = "Unselectable";
      categoryMap[UnitCategory::CanNotUseAirStaging       ] = "CanNotUseAirStaging";
      categoryMap[UnitCategory::ReclaimFriendly           ] = "ReclaimFriendly";
    }
    if (categoryMap.count(input))
      return categoryMap[input];
    throw std::runtime_error("Category not found");
  }

  std::vector<UnitCategory>& allUnitCategories() {
    static std::vector<UnitCategory> all = { 
      UnitCategory::AbilityButton,
      UnitCategory::Aeon,
      UnitCategory::Air,
      UnitCategory::AirStagingPlatform,
      UnitCategory::AntiAir,
      UnitCategory::AntiMissile,
      UnitCategory::AntiNavi,
      UnitCategory::AntiSubmarine,
      UnitCategory::Artillery,
      UnitCategory::Battleship,
      UnitCategory::Benign,
      UnitCategory::Bomber,
      UnitCategory::Bot,
      UnitCategory::BuildByCommander,
      UnitCategory::BuildByExperimentalSub,
      UnitCategory::BuildByLandTier2Factory,
      UnitCategory::BuildByLandTier3Factory,
      UnitCategory::BuildByQuantumGate,
      UnitCategory::BuildByT1Factory,
      UnitCategory::BuildByT2Factory,
      UnitCategory::BuildByT3Commander,
      UnitCategory::BuildByT3Engineer,
      UnitCategory::BuildByT3Factory,
      UnitCategory::BuildByTier1Engineer,
      UnitCategory::BuildByTier2Commander,
      UnitCategory::BuildByTier2Engineer,
      UnitCategory::CanNotUseAirStaging,
      UnitCategory::CanTransportCommander,
      UnitCategory::Capture,
      UnitCategory::Carrier,
      UnitCategory::Civilian,
      UnitCategory::Civillian,
      UnitCategory::Command,
      UnitCategory::Construction,
      UnitCategory::ConstructionSortDown,
      UnitCategory::CounterIntelligence,
      UnitCategory::Cruiser,
      UnitCategory::Cybran,
      UnitCategory::Defense,
      UnitCategory::DefensiveBoat,
      UnitCategory::Destroyer,
      UnitCategory::DirectFire,
      UnitCategory::DragBuild,
      UnitCategory::Economic,
      UnitCategory::EnergyProduction,
      UnitCategory::EnergyStorage,
      UnitCategory::Engineer,
      UnitCategory::EngineerStation,
      UnitCategory::Experimental,
      UnitCategory::Factory,
      UnitCategory::FavorsWater,
      UnitCategory::FerryBeacon,
      UnitCategory::FieldEngineer,
      UnitCategory::Frigate,
      UnitCategory::Gate,
      UnitCategory::GroundAttack,
      UnitCategory::HighAltitudeAir,
      UnitCategory::HighPriorityAir,
      UnitCategory::Hover,
      UnitCategory::HydroCarbon,
      UnitCategory::IndirectFire,
      UnitCategory::InsignificantUnit,
      UnitCategory::Intelligence,
      UnitCategory::Invulnerable,
      UnitCategory::Land,
      UnitCategory::LightBoat,
      UnitCategory::MassExtraction,
      UnitCategory::MassFabrication,
      UnitCategory::MassProduction,
      UnitCategory::MassStorage,
      UnitCategory::Mobile,
      UnitCategory::MobileSonar,
      UnitCategory::NavAL,
      UnitCategory::NavalCarrier,
      UnitCategory::NeedMobileBuild,
      UnitCategory::NoFormation,
      UnitCategory::Nuke,
      UnitCategory::NukeSubmarine,
      UnitCategory::Omni,
      UnitCategory::Operation,
      UnitCategory::Optics,
      UnitCategory::OrbitalSystem,
      UnitCategory::OverlayAntiAir,
      UnitCategory::OverlayAntiNavi,
      UnitCategory::OverlayCounterIntelligence,
      UnitCategory::OverlayDefense,
      UnitCategory::OverlayDirectFire,
      UnitCategory::OverlayIndirectFire,
      UnitCategory::OverlayMisc,
      UnitCategory::OverlayOmni,
      UnitCategory::OverlayRadar,
      UnitCategory::OverlaySonar,
      UnitCategory::PatrolHelper,
      UnitCategory::Pod,
      UnitCategory::PodStagingPlatform,
      UnitCategory::ProductDL,
      UnitCategory::ProductFA,
      UnitCategory::ProductSC1,
      UnitCategory::Radar,
      UnitCategory::RallyPoint,
      UnitCategory::Rebuilder,
      UnitCategory::Reclaim,
      UnitCategory::ReclaimFriendly,
      UnitCategory::Reclaimable,
      UnitCategory::Repair,
      UnitCategory::Satellite,
      UnitCategory::Scout,
      UnitCategory::Selectable,
      UnitCategory::Seraphim,
      UnitCategory::Shield,
      UnitCategory::ShowAttackReticle,
      UnitCategory::ShowQueue,
      UnitCategory::Silo,
      UnitCategory::Size12,
      UnitCategory::Size16,
      UnitCategory::Size20,
      UnitCategory::Size4,
      UnitCategory::Size8,
      UnitCategory::Sonar,
      UnitCategory::SortConstruction,
      UnitCategory::SortDefense,
      UnitCategory::SortEconomy,
      UnitCategory::SortIntel,
      UnitCategory::SortStrategic,
      UnitCategory::SpecialHighPriority,
      UnitCategory::SpecialLowPriority,
      UnitCategory::StationIsPod,
      UnitCategory::Strategic,
      UnitCategory::Structure,
      UnitCategory::SubCommander,
      UnitCategory::Submersible,
      UnitCategory::T1Submarine,
      UnitCategory::T2Submarine,
      UnitCategory::TacticalMissilePlatform,
      UnitCategory::Tank,
      UnitCategory::TargetChaser,
      UnitCategory::Tech1,
      UnitCategory::Tech2,
      UnitCategory::Tech3,
      UnitCategory::TeleportBeacon,
      UnitCategory::TransportFocus,
      UnitCategory::TransportT1,
      UnitCategory::TransportT2,
      UnitCategory::TransportT3,
      UnitCategory::Transportation,
      UnitCategory::UEF,
      UnitCategory::Unselectable,
      UnitCategory::Untargetable,
      UnitCategory::VerifyMissleUI,
      UnitCategory::VisibleToRecon,
      UnitCategory::Wall
    };
    return all;
  }
}