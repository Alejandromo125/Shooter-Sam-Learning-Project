# Shooter Sam – Learning Project

A third-person shooter built with **Unreal Engine 5.6** and **C++**, created as a hands-on learning project for hitscan weapons, enemy AI with Behavior Trees, and HUD/UMG integration.

The player runs through the level with a gun, fights enemy shooters that spot, chase and shoot back, and keeps an eye on a health bar in the HUD.

> **Note:** This is a personal learning project, not a production-ready game. Code and structure may change as I keep learning.

<!-- Optional: add a screenshot or GIF of the game here
![Gameplay](Docs/gameplay.gif)
-->

## Features

- **Third-person character** (`AShooterSamCharacter`) with Enhanced Input: move, look, jump and shoot
- **Hitscan weapon** (`AGun`): line trace along the shooter's view direction on a dedicated `Bullet` trace channel, with Niagara muzzle flash and impact effects, and damage applied through Unreal's damage system
- **Enemy AI** (`AShooterAI`) driven by a **Behavior Tree** with custom C++ nodes:
  - `BTService_PlayerLocationIfSeen` – stores the player's position and focuses on them while there is line of sight
  - `BTService_LastKnownLocation` – remembers where the player was last seen
  - `BTTask_Shoot` – makes the AI character fire its gun
  - `BTTask_ClearBlackBoardValue` – clears a Blackboard key
- **Health and death** handling on the character, including a **HUD health bar** (`UHUDWidget`, UMG)
- **Shared weapon logic** – player and AI characters use the same `AGun` and the same `PullTrigger()` function
- **Third Person template variants** (`Combat`, `Platforming`, `SideScrolling`) kept in the project from the original UE template (see below)

## How It Works

```
AShooterSamGameMode (BeginPlay)
   └─ finds every AShooterAI in the level
        └─ StartBehaviourTree(player)  →  runs the enemy Behavior Tree and sets "StartingLocation"

Behavior Tree (enemy)
   ├─ BTService_PlayerLocationIfSeen / LastKnownLocation  →  update Blackboard from line of sight
   └─ BTTask_Shoot  →  AShooterSamCharacter::ShootAI()  →  AGun::PullTrigger()

AGun::PullTrigger()
   └─ line trace (Bullet channel) → spawn impact effect → ApplyDamage
        └─ AShooterSamCharacter::OnDamageTaken → update health, HUD bar, death
```

- **Player shooting:** the `ShootAction` input calls `AGun::PullTrigger()`.
- **Death:** when health reaches 0 the character is flagged as not alive, collision is disabled and it is detached from its controller. AI stops shooting once the player is dead.

## Tweakable Properties

Editable in the Blueprints derived from these classes:

| Class | Property | Default |
|-------|----------|---------|
| `AShooterSamCharacter` | `maxHealth` | 100 |
| `AShooterSamCharacter` | `gunClassBluePrint` | – (assign a Gun Blueprint) |
| `AGun` | `MaxRange` | 1000 |
| `AGun` | `bulletDamage` | 10 |
| `AGun` | `impactParticleSystem` | – (Niagara system) |
| `AShooterAI` | `enemyAI_BT` | – (Behavior Tree asset) |
| `AShooterSamPlayerController` | `hudWidgetClass` | – (HUD widget Blueprint) |

## Requirements

- **Unreal Engine 5.6** (via the Epic Games Launcher)
- **Visual Studio 2022** with the components listed in [`.vsconfig`](.vsconfig) (*Game development with C++*)
- **Windows 10/11** (recommended)
- Git (and Git LFS if you add large binary assets)

The C++ module depends on: `Core`, `CoreUObject`, `Engine`, `InputCore`, `EnhancedInput`, `AIModule`, `StateTreeModule`, `GameplayStateTreeModule`, `UMG`, `Slate` and `Niagara`.

Project plugins enabled: `StateTree`, `GameplayStateTree`, `ModelingToolsEditorMode` (editor only), `CascadeToNiagaraConverter`.

## Getting Started

### 1. Clone the repository

```bash
git clone https://github.com/Alejandromo125/Shooter-Sam-Learning-Project.git
cd Shooter-Sam-Learning-Project
```

### 2. Install the required Visual Studio components

Open `.vsconfig` with the **Visual Studio Installer** (*More → Import configuration*).

### 3. Generate project files

Right-click `ShooterSam.uproject` and choose **Generate Visual Studio project files**.

### 4. Build and run

**From Visual Studio**
1. Open `ShooterSam.sln`.
2. Select the **Development Editor** configuration and the **Win64** platform.
3. Build and start (`F5`).

**From the Unreal Editor**
1. Double-click `ShooterSam.uproject`.
2. When prompted, rebuild the missing modules.

The project opens on `TestLevel` (`Content/MyStuff/Levels`) by default.

## Controls

| Action | Input |
|--------|-------|
| Move | WASD |
| Look | Mouse |
| Jump | SpaceBar |
| Shoot | LeftClick |

Bindings live in the input mapping contexts assigned to the player controller (`DefaultMappingContexts`).

## Project Structure

```
Shooter-Sam-Learning-Project/
├── Config/                       # Engine, input, game and editor settings
├── Content/                      # Maps, Blueprints, UI, meshes, effects, audio
├── Source/
│   └── ShooterSam/
│       ├── ShooterSamCharacter.* # Player/AI character: input, health, gun ownership
│       ├── Gun.*                 # Hitscan weapon (trace, effects, damage)
│       ├── ShooterAI.*           # AI controller that runs the Behavior Tree
│       ├── BTTask_Shoot.*        # Behavior Tree task: fire the gun
│       ├── BTTask_ClearBlackBoardValue.*
│       ├── BTService_PlayerLocationIfSeen.*
│       ├── BTService_LastKnownLocation.*
│       ├── ShooterSamGameMode.*  # Starts the AI Behavior Trees on BeginPlay
│       ├── ShooterSamPlayerController.* # Input contexts, HUD creation
│       ├── HUDWidget.*           # UMG health bar widget
│       ├── Variant_Combat/       # From the UE Third Person template
│       ├── Variant_Platforming/  # From the UE Third Person template
│       └── Variant_SideScrolling/# From the UE Third Person template
├── ShooterSam.uproject
├── .vsconfig
└── LICENSE
```

### About the `Variant_*` folders

The project was created from Unreal Engine's **Third Person C++ template**, which ships with three optional gameplay variants (a melee combat character, a platforming character and a side-scrolling character). They are still compiled with the project but are **not used by the shooter gameplay**. The shooter-specific code is the set of files listed above outside the `Variant_*` folders.

## What I'm Learning

- Hitscan weapons with line traces and custom collision channels
- AI with Behavior Trees: custom tasks, services and Blackboard keys
- Sharing weapon logic between player and AI characters
- Enhanced Input, UMG HUDs and Niagara effects
- Unreal's damage and event system

## Contributing

This is a personal learning project, but feedback and suggestions are welcome. Feel free to open an [issue](https://github.com/Alejandromo125/Shooter-Sam-Learning-Project/issues) or submit a pull request.

## License

Distributed under the **MIT License**. See [`LICENSE`](LICENSE) for details.

## Author

**Alejandro** – [@Alejandromo125](https://github.com/Alejandromo125)

