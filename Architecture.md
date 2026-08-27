# SoulSlice Architecture

This document defines the intended project structure for the SoulSlice Unreal Engine game.

## Core Philosophy

- Thin Characters
  - The character actor should stay lightweight.
  - Most gameplay logic lives in components, abilities, and systems.
- GAS owns combat
  - Damage, stamina, poise, attack logic, and status effects should be driven by Ability System Components and Gameplay Abilities.
- Components for non-ability systems
  - Movement, lock-on, camera targeting, and interaction logic live in components.
- Interfaces for communication
  - Use interfaces for loosely coupled communication between actors and systems.
- Data Assets / Data Tables for tuning
  - Balance values, weapon stats, enemy data, and gameplay tuning should be data-driven.

## Recommended Folder Structure

```text
SoulSlice/
├── Source/
│   ├── SoulSlice/
│   │   ├── Characters/
│   │   │   ├── SoulCharacterBase.h
│   │   │   ├── SoulCharacterBase.cpp
│   │   │   ├── Player/
│   │   │   │   ├── SoulPlayerCharacter.h
│   │   │   │   └── SoulPlayerCharacter.cpp
│   │   │   └── Enemies/
│   │   │       ├── SoulEnemyCharacter.h
│   │   │       └── SoulEnemyCharacter.cpp
│   │   │
│   │   ├── Components/
│   │   │   ├── Movement/
│   │   │   │   ├── SoulMovementComponent.h
│   │   │   │   └── SoulMovementComponent.cpp
│   │   │   ├── LockOn/
│   │   │   │   ├── LockOnComponent.h
│   │   │   │   └── LockOnComponent.cpp
│   │   │   └── Camera/
│   │   │       ├── SoulCameraComponent.h
│   │   │       └── SoulCameraComponent.cpp
│   │   │
│   │   ├── AbilitySystem/
│   │   │   ├── AttributeSets/
│   │   │   │   ├── SoulAttributeSet.h
│   │   │   │   └── SoulAttributeSet.cpp
│   │   │   ├── Abilities/
│   │   │   │   ├── GA_MeleeAttack.h
│   │   │   │   ├── GA_MeleeAttack.cpp
│   │   │   │   ├── GA_HeavyAttack.h
│   │   │   │   ├── GA_HeavyAttack.cpp
│   │   │   │   ├── GA_Dodge.h
│   │   │   │   ├── GA_Dodge.cpp
│   │   │   │   ├── GA_Heal.h
│   │   │   │   └── GA_Heal.cpp
│   │   │   ├── Effects/
│   │   │   │   ├── GE_Damage.h
│   │   │   │   ├── GE_StaminaCost.h
│   │   │   │   ├── GE_PoiseDamage.h
│   │   │   │   └── GE_Heal.h
│   │   │   └── Tags/
│   │   │       └── SoulGameplayTags.h
│   │   │
│   │   ├── Interfaces/
│   │   │   ├── Damageable.h
│   │   │   ├── LockOnTarget.h
│   │   │   └── Interactable.h
│   │   │
│   │   ├── Data/
│   │   │   ├── Weapons/
│   │   │   │   ├── WeaponDataAsset.h
│   │   │   │   └── WeaponDataAsset.cpp
│   │   │   └── Enemies/
│   │   │       ├── EnemyDataAsset.h
│   │   │       └── EnemyDataAsset.cpp
│   │   │
│   │   ├── AI/
│   │   │   ├── SoulAIController.h
│   │   │   ├── SoulAIController.cpp
│   │   │   ├── BT/
│   │   │   └── StateTree/
│   │   │
│   │   ├── UI/
│   │   │   ├── Widgets/
│   │   │   └── HUD/
│   │   │
│   │   └── System/
│   │       ├── SoulGameMode.h
│   │       ├── SoulGameMode.cpp
│   │       ├── SoulPlayerController.h
│   │       └── SoulPlayerController.cpp
│   │
│   └── SoulSlice.Build.cs
│
├── Config/
├── Content/
├── Saved/
├── Intermediate/
├── Binaries/
├── SoulSlice.uproject
├── SoulSlice.sln
├── README.md
├── Architecture.md
└── .gitignore
```

## Responsibility Split

### Characters
- `SoulCharacterBase`
  - Base class for player and enemies.
  - Owns `AbilitySystemComponent`, `AttributeSet`, and common state.
  - Keeps actor logic thin.

- `SoulPlayerCharacter`
  - Owns player-specific input, camera reference, and gameplay state.
  - Does not implement combat logic directly.

- `SoulEnemyCharacter`
  - Enemy-specific behavior and enemy AI integration.

### Components
- `SoulMovementComponent`
  - Handles movement, acceleration, sprinting, dodging, strafing, and grounded logic.
  - Keeps route movement separate from combat abilities.

- `LockOnComponent`
  - Handles target acquisition and target retention.

- `SoulCameraComponent`
  - Handles camera follow, orbit, spring arm logic, and camera collision.

### Ability System
- `SoulAttributeSet`
  - Health, stamina, poise, and other combat stats.

- Gameplay Abilities
  - `GA_MeleeAttack`
  - `GA_HeavyAttack`
  - `GA_Dodge`
  - `GA_Heal`
  - optional weapon art or special move abilities

- Gameplay Effects
  - Damage, stamina cost, poise damage, healing, and status applications

### Data
- `WeaponDataAsset`
  - Weapon stats, animation tags, damage values, attack ranges

- `EnemyDataAsset`
  - Enemy profile tuning

### AI
- `SoulAIController`
  - Controls enemy behavior and decision making.
- Behavior Tree / State Tree
  - Enemy pursuit, attack, dodge, and idle logic

## Recommended Rules

1. Character class should not directly contain all gameplay logic.
2. Movement-specific logic belongs in `SoulMovementComponent`.
3. Combat logic belongs in GAS abilities and effects.
4. Interfaces should be used for cross-system communication when needed.
5. Tuning values should live in Data Assets or Data Tables, not hardcoded.

## Suggested Next Step

Build the following in order:

1. `SoulCharacterBase`
2. `SoulPlayerCharacter`
3. `SoulMovementComponent`
4. `SoulAttributeSet`
5. `GA_Dodge`
6. `LockOnComponent`
7. `GA_MeleeAttack`
8. Camera system

This keeps the project modular and makes it easier to expand into a full Souls-like combat system.
