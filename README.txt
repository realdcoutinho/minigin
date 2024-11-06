https://github.com/realdcoutinho/minigin/tree/main

Scene and Scene Manager Overview
Scene
Each Scene represents a potential game level and is uniquely identified by a name. Scenes manage their own timers and use std::shared_ptr for efficient memory management.

Scene Manager
The SceneManager manages all scenes and controls the active scene and its timer. It offers functions to create, retrieve, and switch scenes efficiently:

CreateScene: Instantiates scenes with a specified name.
SetActiveScene: Switches the active scene by name or reference.
GetSceneByName: Retrieves a scene by name for specific operations.
This setup provides a flexible and scalable framework for game development, allowing easy management of game levels and resources.

____

Timer Functionality Overview
Scene-Specific Timers:
Each Scene is equipped with an individual timer, allowing each scene to operate under unique timing conditions. This functionality is vital for games that require variable speed updates or when different gameplay segments demand distinct timing mechanisms. Moreover, when scenes switch—such as transitioning to a pause menu—scene-specific timers ensure that only the active scene’s events and updates are processed, preventing unwanted game actions during inactive states.

Global Timer:
Beyond scene-specific timers, the engine includes a global timer managed by the TimeManager. This global timer is continuously updated and is not tied to any particular scene. It's particularly useful for managing events that transcend individual scenes, such as player states or UI updates, providing a consistent time reference regardless of scene changes.

Implementation:

Scene Timers: Managed by TimeManager, each scene timer can be started, paused, or reset independently, allowing flexible control over scene dynamics.
Global Timer: Provides elapsed time data that can be accessed by any part of the game, ensuring that time-sensitive operations outside of the scene context are synchronized with the game’s overall timeline.
This dual timer system enhances the engine’s versatility, supporting both isolated scene operations and overarching game functions seamlessly.

____

Input Management Overview
Each Scene in the engine is associated with its own input system to ensure inputs are processed exclusively within the active scene. This setup prevents input conflicts or duplications across different scenes, enhancing game responsiveness and accuracy in input handling. Scene-specific input management is crucial for maintaining the integrity of player interactions, especially when switching scenes or accessing menus, where input from a previously active scene needs to be isolated.

___

Event Dispatch Mechanism Overview
The event dispatch mechanism is pivotal for managing interactions within the game engine, involving IEvents and IEventListeners. Here’s a streamlined outline:

Components
IEvent: Base interface for events.
IEventListener: Interface for classes that respond to events, specifying event handling and applicable event types.
BaseEvent: Concrete event implementation with identifiers and sender details.
Event Dispatching and Listening
Subscription: Listeners subscribe by indicating their interest in specific event types. The dispatcher maintains a mapping of event types to listeners.
Event Dispatching: Events are dispatched into an EventQueue and processed sequentially to notify relevant listeners.
Threaded Processing
Original Design: Designed for asynchronous processing in a separate thread to enhance performance.
Safety Reversion: Due to thread safety concerns like race conditions, the default setup reverted to single-threaded processing.
Re-enabling Threading: Developers can activate multithreaded processing through the EventDispatcher by managing the event processing thread.
Thread Safety and Flexibility
Safety Tools: Mutexes and atomic flags secure access to the event queue during multithreaded operations.
Developer Control: The engine offers a choice between single-threaded reliability and multithreaded performance, adaptable to the game’s complexity.
This framework provides a flexible and robust system for event management, balancing performance with safety to cater to different development needs.

__

Game Mode Overview
The Game Mode mechanism in the game engine acts as the central brain, orchestrating high-level game logic and state management across different scenes and levels. Here’s a detailed explanation of its functionality and usage:

Purpose and Functionality
Central Controller: Game Mode serves as the central control system for managing game states that aren't tied to specific scenes or levels, such as player progress, transitioning between levels, and holding game-wide data.
Game Specific: Each game mode is tailored to specific game needs. This means developers must create custom implementations of the GameMode class to suit their particular game mechanics and rules.
Implementation Details
Abstract Base Class: The GameMode class is an abstract base, meaning it cannot be instantiated on its own. It provides virtual functions like Update (to handle frame-by-frame updates) and IsGameRunning (to check the game's active state), which must be overridden in derived classes.
Game Mode Manager: The GameModeManager manages different game modes, maintaining references to active game modes and facilitating their creation. Using templating, it ensures that only classes derived from GameMode can be instantiated, enforcing type safety and relevance.
Usage Scenario
Managing Game Flow: Game Modes control overarching game events and transitions, like loading and ending levels or managing persistent player data across game sessions.
Creating Custom Game Modes: Developers create custom game modes by extending the GameMode class, implementing the necessary virtual methods to integrate with the game’s unique rules and logic.
Flexibility and Control
Developer Customization: Since the base class cannot be instantiated directly, developers are encouraged to define specific game modes that reflect the gameplay mechanics required for their games.
Managed by Game Mode Manager: The creation and switching of game modes are handled by GameModeManager, which uses a Singleton pattern to ensure there is a centralized, consistent point of control.
This structure provides a robust framework for managing different aspects of game logic that are independent of the in-level mechanics, thereby offering a scalable solution for game development that accommodates complex game flows and state management.