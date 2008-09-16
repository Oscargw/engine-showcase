#include "FileManager.h"

#include <windows.h>
#include <sstream>
#include "physfs.h"
#include "../Logging/Logger.h"
#include "../Common/Paths.hpp"
#include "../Exceptions/UnInitializedException.hpp"
#include "../Exceptions/AlreadyInitializedException.hpp"

static FileManager* g_FileManagerInstance = 0;

FileManager* FileManager::GetInstance( )
{
	if ( g_FileManagerInstance == 0 )
	{
		throw UnInitializedException( );
	}

	return g_FileManagerInstance;
}

void FileManager::Release( )
{
	Logger::GetInstance( )->Info( "Releasing the File Manager" );

	PHYSFS_deinit( );

	delete g_FileManagerInstance;
	g_FileManagerInstance = 0;
}

const bool FileManager::Initialize( )
{
	if ( g_FileManagerInstance != 0 )
	{
		std::string errorMessage = "FileMananger has already been Intialized";
		Logger::GetInstance( )->Fatal( errorMessage );
		throw AlreadyInitializedException( errorMessage );
	}

	Logger::GetInstance( )->Info( "Initializing the File Manager" );

	g_FileManagerInstance = new FileManager( );

	return true;	
}

FileManager::FileManager( )
{
	PHYSFS_init( 0 );
	PHYSFS_addToSearchPath( Paths::GetGameFolderPath( ).c_str( ), 1 );
}

bool FileManager::FileExists( const std::string filePath ) const
{
	return PHYSFS_exists( filePath.c_str( ) );
}

bool FileManager::AddFileStore( const std::string filePath )
{
	std::stringstream logMessage;
	logMessage << "Adding " << filePath << " to File System Path";
	Logger::GetInstance( )->Debug( logMessage.str( ) );

	int result = PHYSFS_addToSearchPath( filePath.c_str( ), 1 );

	return ( result > 0 );
}

FileBuffer* FileManager::GetFile( const std::string filePath ) const
{
	std::stringstream logMessage;
	logMessage << "Loading File: " << filePath;
	Logger::GetInstance( )->Debug( logMessage.str( ) );

	FileBuffer* fileBuffer = 0;

	if ( PHYSFS_exists( filePath.c_str( ) ) )
	{
		PHYSFS_file *pFile = PHYSFS_openRead( filePath.c_str( ) );
		
		int fileLength = PHYSFS_fileLength( pFile );
		fileBuffer = new FileBuffer( );
		fileBuffer->fileBytes = new CHAR[ fileLength ];
		fileBuffer->fileSize = PHYSFS_read( pFile, fileBuffer->fileBytes, 1, fileLength );
		fileBuffer->filePath = filePath;
		PHYSFS_close( pFile );
	}

	return fileBuffer;
}