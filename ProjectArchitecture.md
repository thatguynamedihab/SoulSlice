# SoulSlice Architecture Document

## 1. Project Overview & Vision
**Project Name:** SoulSlice
**Engine:** Unreal Engine 5 (C++)
**Scope:** A focused, vertical slice of a Souls-like combat encounter. Not a full game, but a highly polished proof of mechanics.
**Core Goal:** Force the use of modern, scalable UE5 architecture (GAS, Interfaces, Data Assets) while avoiding the "fat base class" inheritance traps of previous projects.

## 2. Core Architectural Pillars
*   **Composition Over Inheritance:** Characters will be empty shells (Pawns) that gain functionality entirely through attached Components. No deep inheritance trees.
*   **GAS-First Design:** The Gameplay Ability System will handle all combat logic, state management, and stat modifications.
*   **Data-Driven:** Gameplay values (weapon damage, enemy stats, stamina costs) will live in Data Assets and Data Tables, not hardcoded in C++ classes.
*   **Interface Polymorphism:** Systems will communicate via Unreal Interfaces (`IDamageable`, `ITargetable`) rather than casting to specific character classes.

---

## 3. Folder & Content Structure
Keep the Content Browser and C++ classes mirrored and organized by feature, not by file type.

*   `/Core/` - Base classes, Game Mode, Game State, Player Controller.
*   `/Characters/` - Base Pawn, Player, Enemies (Keep these classes as empty as possible).
*   `/Components/` - All custom Actor Components (Input, Camera, Target Lock).
*   `/GAS/` 
    *   `/Abilities/` - Gameplay Abilities (GA_Attack, GA_Dodge).
    *   `/Effects/` - Gameplay Effects (GE_Damage, GE_StaminaRegen).
    *   `/Cues/` - Gameplay Cues (GC_ImpactSpark, GC_Footstep).
    *   `/Attributes/` - Attribute Sets.
*   `/Data/` - Data Assets, Data Tables, and Curve Tables.
*   `/AI/` - Behavior Trees, Blackboards, EQS (Environment Query System), AI Controllers.
*   `/Interfaces/` - Blueprint/C++ Interfaces.

---

## 4. Character Architecture (The Anti-Fat Base)
Instead of an `ABaseCharacter` with hundreds of variables and functions, the Character class will only act as an initialization hub.

*   **The Pawn:** Only responsible for mesh setup, capsule collision, and initializing components.
*   **Movement Component:** Custom or heavily modified UE Character Movement Component (handles root motion, dodge momentum, lock-on strafing).
*   **Camera Component:** Handles Spring Arm, lag, and pitch limits.
*   **Ability System Component (ASC):** The heart of the character. Handles attribute initialization and ability granting.
*   **Combat Component:** Handles non-GAS combat logic (e.g., managing the lock-on array, calculating hitboxes/weapon collision).

*Rule of Thumb:* If a function is getting too long, or a variable doesn't need to be accessed by *every* character, it belongs in a Component or the ASC, not the Character class.

---

## 5. Gameplay Ability System (GAS) Blueprint

### A. Attributes (`USoulAttributeSet`)
Keep attributes strictly to numbers. Logic belongs in Abilities/Effects.
*   **Vital Stats:** Health, MaxHealth, Stamina, MaxStamina, Poise, MaxPoise.
*   **Regen Rates:** StaminaRegenRate, PoiseRegenRate, HealthRegenRate.
*   **Combat Stats:** BaseDamage, BaseDefense, StaggerThreshold.
*   *Meta Stats (Read-only/Calculated):* IncomingDamage (used to calculate final damage before applying to Health).

### B. Gameplay Tags
Tags are the state machine of GAS. They dictate what a character can and cannot do.
*   **State Tags:** `State.Dead`, `State.Dodging`, `State.Blocking`, `State.Staggered`.
*   **Action Tags:** `Action.Attacking`, `Action.Drinking`.
*   **Immunity Tags:** `Immunity.Stagger`, `Immunity.Interrupt`.
*   **Hit Tags:** `Hit.Critical`, `Hit.Backstab`.

### C. Gameplay Abilities (GAs)
GAs are the "verbs" (Attack, Dodge, Parry).
*   **Commitment:** Every ability must have a "commit" phase (locking the player out of other actions via Tags) and a "recovery" phase.
*   **Costs:** Abilities should automatically deduct Stamina/Mana via Gameplay Effects upon activation.
*   **Blocking:** Use Tag requirements. (e.g., `GA_LightAttack` requires `!State.Dodging` and `!State.Dead`).

### D. Gameplay Effects (GEs)
GEs are the only things allowed to change Attributes.
*   **Instant:** Weapon damage, falling damage, stamina cost of a dodge.
*   **Duration:** Poison, stamina regeneration over time, temporary buffs from a weapon buff.
*   **Infinite:** Passive armor defense bonuses applied on equipment equip.

---

## 6. Interface Strategy
To avoid the casting issues from TopDownSlice, the game world will interact through strict contracts.

*   **`IDamageable`**: Requires a function to receive a Gameplay Effect or Damage payload. Both the Player and Enemies implement this.
*   **`ITargetable`**: Requires functions to get the lock-on socket/location and to register as a valid target for the Combat Component's sphere trace.
*   **`IInteractable`**: For doors, levers, and fog walls. Requires an `OnInteract` function and a way to display a UI prompt.

*Rule of Thumb:* If the Player needs to talk to an Enemy, a Door, or a Pickup, they cast to the Interface, NEVER to the specific class.

---

## 7. Data-Driven Design
Hardcoding stats in C++ or Blueprints is strictly prohibited.

*   **`UWeaponDataAsset`**: Contains weapon mesh, animation montages, combo timing windows, and the Gameplay Effects to apply on hit.
*   **`UEnemyConfigAsset`**: Contains AI behavior tree, base attribute values (passed to the AttributeSet on spawn), and loot tables.
*   **Curve Tables**: Used for scaling stamina costs or damage based on player level or upgrade tiers.

---

## 8. AI & Enemy Architecture
Enemies should use the exact same GAS setup as the Player to ensure consistency (e.g., an enemy can be staggered using the same Poise logic as the player).

*   **AI Controller**: Handles high-level decision making and perception (sight/hearing).
*   **Behavior Tree (BT)**: The "brain." Uses Blackboard keys to track the player.
    *   *Crucial Integration:* The BT should read Gameplay Tags. (e.g., "If Player has `State.Dodging` tag, do not attack, wait for recovery").
*   **Environment Query System (EQS)**: Used for tactical positioning (finding a spot to dodge to, finding the edge of a cliff to push the player off).

---

## 9. Next Steps & Milestones
1.  **Phase 1: The Shell:** Setup Project, Folder Structure, Base Pawn, Camera, and Basic Movement (No GAS yet).
2.  **Phase 2: The Engine:** Implement ASC, Attribute Set, and basic Gameplay Tags. Prove that Health/Stamina can be modified via GEs.
3.  **Phase 3: The Verbs:** Create GA_Dodge and GA_LightAttack. Hook up costs and animation montages.
4.  **Phase 4: The Foe:** Create a basic Grunt enemy, implement the `IDamageable` interface, and setup a basic Behavior Tree.
5.  **Phase 5: The Loop:** Connect it all. Player attacks enemy, enemy reacts, enemy attacks player, player dodges.