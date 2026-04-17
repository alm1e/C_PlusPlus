# Unreal Engine 5 Multiplayer Combat & Inventory Prototype

A gameplay prototype built in **Unreal Engine 5** using **C++ and Blueprints**, focused on **multiplayer melee combat**, **server-authoritative interactions**, and **inventory/pickup systems**.

## Author

**Almas Karnakbayev**  
Gameplay programming focused Unreal Engine developer

## Links
- Demonstration video: https://youtu.be/EjSa7pfZhjI
- Portfolio: https://artstation.com/almie
- GitHub: https://github.com/alm1e
- LinkedIn: https://www.linkedin.com/in/alm1e
- YouTube: https://www.youtube.com/@AlmieGameDev/videos

## Overview

This project demonstrates a networked gameplay setup where players can:

- attack other players in multiplayer
- apply damage through server-side logic
- play replicated attack and hit reaction animations
- pick up items into an inventory
- interact with world items through a pickup hint/highlight flow
- combine C++ gameplay code with Blueprint-driven UI and interaction logic

The main goal of this prototype was to practice **gameplay programming**, **multiplayer logic**, and **debugging client-server behavior** in Unreal Engine 5.

---

## Main Features

### Multiplayer Melee Combat
- server-authoritative melee attack flow
- replicated attack execution
- weapon trace-based hit detection
- damage application through Unreal damage flow
- hit reaction montage playback across network
- multiplayer testing with server + client windows

### Inventory & Pickup System
- item pickup through interaction input
- inventory component integration
- item data extraction from pickup actors
- pickup hint widget
- pickup highlight logic
- server-side item validation before adding to inventory
- item removal from world after successful pickup

### UI
- inventory widget
- pickup hint widget
- player health widget
- inventory open/close input mode switching
- mouse cursor toggle for inventory interaction

---

## Tech Stack

- **Unreal Engine 5**
- **C++**
- **Blueprints**
- **Enhanced Input**
- **UMG**
- **UE networking / replication**

---

## Architecture Notes

The project uses a mixed **C++ + Blueprint** workflow:

### C++ handles
- core character logic
- input binding
- server RPCs
- multiplayer combat flow
- damage handling
- replicated animation calls
- communication between gameplay systems

### Blueprints handle
- UI widgets and presentation
- inventory widget behavior
- pickup hint/highlight presentation
- some interaction glue logic
- visual setup and iteration

This approach was used to keep gameplay systems programmable in C++ while still allowing fast visual iteration in Blueprints.

---

## Implemented Gameplay Flow

### Combat Flow
1. Player presses attack input.
2. Character sends attack request to combat component.
3. Server validates and processes attack logic.
4. Attack montage is played for all players through replicated logic.
5. Weapon trace checks for hit targets.
6. Damage is applied through Unreal's damage system.
7. Hit target receives damage and plays hit reaction montage.

### Pickup Flow
1. Player overlaps or looks at a pickup actor.
2. Pickup hint/highlight is shown.
3. Player presses interact input.
4. Character sends pickup request to the server.
5. Server validates pickup actor and distance.
6. Server extracts item data and amount.
7. Item is added to inventory component.
8. Pickup reference is cleared and actor is removed from world.
9. UI hint/highlight is updated.

---

## Multiplayer Focus

A major part of this prototype was debugging and fixing multiplayer-specific issues such as:

- server-only logic working while client-side visuals did not
- old Blueprint logic conflicting with new C++ flow
- missing component targets
- montage playback not appearing on clients
- incorrect setup on newly created character Blueprints
- replication issues caused by visual logic remaining in old Blueprint events

This project helped reinforce the difference between:
- local input
- server authority
- multicast visual feedback
- replicated gameplay state

---

## Key Systems

- `ATestCharacter`
- `UCombatComponent`
- `UHealthComponent`
- `UInventoryComponent`

### Example responsibilities

#### `ATestCharacter`
- binds Enhanced Input actions
- opens/closes inventory
- sends pickup requests to the server
- routes attack requests
- plays hit reactions and attack montages through replicated calls

#### `UCombatComponent`
- handles attack requests
- controls attack timing/cooldown
- triggers attack-related events

#### `UInventoryComponent`
- stores item slots
- validates item addition
- handles stacking logic

#### `UHealthComponent`
- manages health / stamina related logic
- processes incoming damage or health changes depending on implementation

---

## What I Practiced In This Project

- building gameplay systems in UE5
- mixing C++ and Blueprint workflows
- using Enhanced Input in C++
- handling multiplayer gameplay architecture
- using server RPCs and multicast RPCs
- integrating UI with gameplay systems
- debugging replication and authority issues
- struct-based item data workflows
- component-based gameplay design

---

## Portfolio Value

This prototype is intended as a **gameplay programming portfolio piece**.  
It shows practical work with:

- multiplayer gameplay logic
- replicated combat interactions
- inventory and item pickup systems
- debugging real UE5 gameplay issues
- C++ gameplay programming with Blueprint integration

---

## Possible Future Improvements

- directional hit reactions
- death / respawn flow
- better health UI binding
- prediction / responsiveness improvements
- equipment system
- drop item flow replication polish
- dedicated enemy or dummy target actor
- sound and VFX integration
- cleaner separation of UI and interaction state
- automated replication testing scenarios

---

## Status

Current prototype state:
- multiplayer combat works
- attack and hit reaction flow works
- inventory works
- pickup hint/highlight works
- item pickup works
- UI widgets are integrated

---


