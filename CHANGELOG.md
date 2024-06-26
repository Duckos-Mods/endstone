# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](http://keepachangelog.com/en/1.0.0/)
and this project adheres to [Semantic Versioning](http://semver.org/spec/v2.0.0.html).

## Unreleased

<small>[Compare with 0.4.6](https://github.com/EndstoneMC/endstone/compare/v0.4.6...HEAD)</small>

### Added

- `Player::performCommand` allows a player to execute a given command. During the command execution, the player is
  temporarily granted the operator permission.
- `Level::getDimension` and `Level::getDimensions` for getting dimensions within a specific level.
- `Actor::getDimension` for getting the dimension that an actor resides in.
- `Player::getGameMode` and `Player::setGameMode` for getting and setting a player's game mode.

### Fixed

- `Actor::getVelocity` now returns the correct velocity when the actor rides a vehicle.

## [0.4.6](https://github.com/EndstoneMC/endstone/releases/tag/v0.4.6) - 2024-05-15

<small>[Compare with 0.4.5](https://github.com/EndstoneMC/endstone/compare/v0.4.5...v0.4.6)</small>

### Fixed

- Improved the detection of Python executable.

## [0.4.5](https://github.com/EndstoneMC/endstone/releases/tag/v0.4.5) - 2024-05-14

<small>[Compare with 0.4.3](https://github.com/EndstoneMC/endstone/compare/v0.4.3...v0.4.5)</small>

### Added

- Bootstrap now protects specific files from overwriting during update.
- Python plugin loader now loads all `*.whl` plugins under the `plguins` folder and their dependencies during server
  start up.

### Fixed

- Scheduler now works on Linux.

## [0.4.3](https://github.com/EndstoneMC/endstone/releases/tag/v0.4.3) - 2024-05-13

<small>[Compare with 0.4.2](https://github.com/EndstoneMC/endstone/compare/v0.4.2...v0.4.3)</small>

### Added

- `Server::getOnlinePlayers` for getting all online players.
- `Player::kick` for kicking a specific player with a custom message.
- `Player::getPing` for getting the average latency of a connected player.
- `Actor::getLocation` and `Actor::getVelocity` for getting the location and velocity of an actor respectively.
- `Actor::getLevel` for getting the `Level` that an actor resides in.

### Changed

- `Level` is no longer created for each `Dimension` in a Minecraft world. Instead, one `Level` now manages multiple
  `Dimension`s.
- `Player::getAddress` now returns a `SocketAddress` instead of `std::string`. `Player::getPort` was removed,
  use `SocketAddress::getPort` instead.
- Executable `endstone` now accepts `--server-folder` instead of `--install-folder`, and `--no-confirm` instead
  of `--install`.
- Endstone server will now ask the user whether to update the Bedrock Dedicated Server if an older version is found.

## [0.4.2](https://github.com/EndstoneMC/endstone/releases/tag/v0.4.2) - 2024-04-30

<small>[Compare with 0.4.1](https://github.com/EndstoneMC/endstone/compare/v0.4.1...v0.4.2)</small>

### Added

- `Level::getDimension` for getting the dimension of a specific level.
- `Player::getAddress` and `Player::getPort` for getting the socket address and port of a specific player, respectively.
- Logs are now written to `logs/latest.log` with rotations.
- Basic scheduler implementation, currently supporting only synchronized task execution.
- `PlayerLoginEvent` is called when a player attempts to log in.

### Changed

- Support for Minecraft v1.20.81 (Bedrock)

### Fixed

- Server no longer crashes when the weather is changed on Linux.

## [0.4.1](https://github.com/EndstoneMC/endstone/releases/tag/v0.4.1) - 2024-04-24

<small>[Compare with 0.4.0](https://github.com/EndstoneMC/endstone/compare/v0.4.0...v0.4.1)</small>

This release focuses on supporting game version v1.20.80, which adds several new features.
Additionally, we add a few useful functions to `Player` and `Server`.

### Added

- Commands executed by players are now logged to the console.
- Message of `/say` command will be logged to the console.
- `PlayerCommandEvent` is called when a player attempts to execute a command.
- `Server::broadcastMessage` for broadcasting messages to all players.
- `BroadcastMessageEvent` is called when a message is broadcast by the server.

### Changed

- Support for Minecraft v1.20.80 - Armored Paws (Bedrock)

### Fixed

- Player permissions are recalculated when the op status is changed.
- Incorrect UUID for Players corrected.

## [0.4.0](https://github.com/EndstoneMC/endstone/releases/tag/v0.4.0) - 2024-04-20

<small>[Compare with 0.3.0](https://github.com/EndstoneMC/endstone/compare/v0.3.0...v0.4.0)</small>

In this release, we added an event system and several basic interfaces for game objects like `Level`, `Actor`
and `Player`.

### Added

- Event system that allows plugins to listen for specific events.
- `ServerLoadEvent` is called when a server is started up.
- `Plugin::registerEventHandler` for registering an event handler in C++ plugins.
- Decorator `@event_handler` for registering an event handler in Python plugins.
- `PluginEnableEvent` and `PluginDisableEvent` are called when a plugin is enabled or disabled.
- `ServerPingListEvent` can be listened to for customizing how the server appears in the client list.
- `ServerCommandEvent` is called when the server executes a command.
- `WeatherChangeEvent` and `ThunderChangeEvent` are called when the weather or thunder status changes in a level.
- Basic interface `endstone::Level` for a level/world.
- Basic interface `endstone::Actor` for entities/actors.
- Basic interface `endstone::Player` for players.
- `Server::getPlayer` for getting a player instance by UUID.
- `Player::sendPopup` and `Player::sendTip` for sending popup and tip messages.
- Stack traces are now printed to the console when an unrecoverable error occurs.
- `PlayerJoinEvent` and `PlayerQuitEvent` are called when a player joins and leaves the server.
- `ActorSpawnEvent` is called when an actor is spawned in the level.
- `ActorRemoveEvent` is called when an actor is removed from the level.
- `PlayerChatEvent` is called when a player sends a message.

### Changed

- Singletons are now managed using `entt::locator`.
- Macro `ENDSTONE_PLUGIN` is improved to simplify the definition of plugin metadata.
- `ColorFormat` and `GameMode` have been moved from `endstone.util` to `endstone` in the Python package.
- Wheels are now built and released with `RelWithDebInfo` configuration to enable stack trace printing.
- Support for Minecraft v1.20.73 (Bedrock)

### Fixed

- Server no longer crashes when `/listd` command is executed.

## [0.3.0](https://github.com/EndstoneMC/endstone/releases/tag/v0.3.0) - 2024-03-21

<small>[Compare with 0.2.0](https://github.com/EndstoneMC/endstone/compare/v0.2.0...v0.3.0)</small>

This is the second release of Endstone with a focus on the permission system and improving the plugin loading
mechanisms.

### Added

- Basic permission systems.
- Enforced Plugin API version checks for C++ and Python plugins to ensure ABI/API compatibility.
- Commands are now defined within the plugin metadata which will be automatically registered when the associated plugin
  is enabled.
- PluginDescription properties are extended to support `website`, `load_order`, `depend`, `soft_depend`, `load_before`,
  and `provides`.

### Changed

- Improved `ENDSTONE_PLUGIN` macro to further simplify the definition of plugin metadata.
- Plugin names and websites are now displayed when using `/version [plugin: PluginName]`.
- Support for Minecraft v1.20.72 (Bedrock)

### Fixed

- C++ plugin loader now respects the `prefix` property of a plugin.

## [0.2.0](https://github.com/EndstoneMC/endstone/releases/tag/v0.2.0) - 2024-03-19

Hello World! This is the first release of Endstone.

### Added

- Basic plugin loader for C++ and Python plugins.
- Basic command system that allows plugins to register custom commands.
