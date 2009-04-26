#include "Game.h"

#include "Logging/Logger.h"
#include "Management/Management.h"

#include "Configuration/Configuration.h"
using namespace Configuration;

#include "State/World.h"
#include "State/WorldLoader.h"

#include "Scripting/ScriptSystem.h"
#include "Input/InputSystem.h"
#include "Renderer/RendererSystem.h"
#include "Geometry/GeometrySystem.h"
#include "Physics/HavokPhysicsSystem.h"
#include "AI/AISystem.h"

#include "Events/Event.h"
#include "Events/EventData.hpp"
using namespace Events;

#include "Exceptions/AlreadyInitializedException.hpp"
#include "Exceptions/UnInitializedException.hpp"

#include "Renderer/Color.hpp"
#include "Scripting/ScriptEvent.hpp"

void Game::Initialize( )
{
	if ( _isInitialized )
	{
		AlreadyInitializedException e ( "Game::Initialize - Attempted to Initialized when the game had already been Initialized" );
		Logger::GetInstance( )->Fatal( e.what( ) );
		throw e;
	}

	// -- Initialize All Singletons

	Logger::Initialize( );
	Management::Initialize( );

	// -- Set Configuration Defaults 

	_configuration = ClientConfiguration::Load( "config/game.cfg" );
	_configuration->SetDefault( "Developer", "console", false );
	_configuration->SetDefault( "Logging", "level", static_cast< int >( FATAL ) );

	LogLevel logLevel = static_cast< LogLevel >( _configuration->Find( "Logging", "level" ).GetValue< int >( ) );
	Logger::GetInstance( )->SetLogLevel( logLevel );

	// -- Initialize All Systems

	ISystemManager* systemManager = Management::GetInstance( )->GetSystemManager( );
	systemManager->RegisterSystem( new GeometrySystem( ) );
	systemManager->RegisterSystem( new HavokPhysicsSystem( ) );
	systemManager->RegisterSystem( new AI::AISystem( ) );
	systemManager->RegisterSystem( new ScriptSystem( _configuration ) );
	systemManager->RegisterSystem( new RendererSystem( _configuration ) );
	systemManager->RegisterSystem( new InputSystem( _configuration ) );
	systemManager->InitializeAllSystems( );

	// -- Setup the World and World Loader

	_world = systemManager->CreateWorld( );
	_worldLoader = new WorldLoader( _world );

	// -- Register Events

	Management::GetInstance( )->GetEventManager( )->AddEventListener( GAME_QUIT, this, &Game::OnGameQuit );
	Management::GetInstance( )->GetEventManager( )->AddEventListener( GAME_LEVEL_CHANGED, this, &Game::OnGameLevelChanged ); 
	Management::GetInstance( )->GetEventManager( )->AddEventListener( GAME_ENDED, this, &Game::OnGameEnded );
	Management::GetInstance( )->GetEventManager( )->QueueEvent( new ScriptEvent( "GAME_INITIALIZED" ) );

	_isInitialized = true;
}

Game::~Game( )
{
	delete _configuration;
}

void Game::Update( float deltaMilliseconds )
{
	if ( !_isInitialized )
	{
		UnInitializedException e( "Game::StartLoop - Cannot Start the Loop when not Initialized" );
		Logger::GetInstance( )->Fatal( e.what( ) );
		throw e;
	}

	_worldLoader->Update( deltaMilliseconds );
	_world->Update( deltaMilliseconds );
	Management::GetInstance( )->Update( deltaMilliseconds );
}

void Game::Release( )
{
	if ( !_isInitialized )
	{
		UnInitializedException e( "Game::Release - Cannot Release when not Initialized" );
		Logger::GetInstance( )->Fatal( e.what( ) );
		throw e;
	}

	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( GAME_QUIT, this, &Game::OnGameQuit );
	Management::GetInstance( )->GetEventManager( )->RemoveEventListener( GAME_LEVEL_CHANGED, this, &Game::OnGameLevelChanged ); 

	_world->Clear( );

	delete _worldLoader;
	delete _world;

	Management::GetInstance( )->Release( );
	Logger::GetInstance( )->Release( );
}

void Game::OnGameQuit( const IEvent* event )
{
	_isQuitting = true;
}

void Game::OnGameLevelChanged( const IEvent* event )
{
	this->OnGameEnded( event );

	LevelChangedEventData* eventData = static_cast< LevelChangedEventData* >( event->GetEventData( ) );

	std::stringstream levelPath;
	levelPath << "/data/levels/" << eventData->GetLevelName( ) << ".yaml";
	
	_worldLoader->Load( levelPath.str( ) );
}

void Game::OnGameEnded( const IEvent* event )
{
	_world->Clear( );

	ISystem* renderSystem = Management::GetInstance( )->GetSystemManager( )->GetSystem( System::Types::RENDER );

	renderSystem->SetProperty( "activeCamera", "default" );
	renderSystem->SetProperty( "ambientColor", Color( 0.0f, 0.0f, 0.0f ) );
	renderSystem->SetProperty( "backgroundColor", Color( 0.0f, 0.0f, 0.0f ) );
	renderSystem->SetProperty( "skyBox", "" );
}

// EOF