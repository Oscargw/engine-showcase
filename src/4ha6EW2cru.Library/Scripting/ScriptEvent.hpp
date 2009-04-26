#ifndef __SCRIPTEVENT_H
#define __SCRIPTEVENT_H

#include "../Events/IEvent.hpp"
#include "../Events/IEventData.hpp"
#include "../Events/EventType.hpp"

/*! A Script Event */
class ScriptEvent : public Events::IEvent
{

public:

	virtual ~ScriptEvent( ) { };

	ScriptEvent( const std::string eventName )
		: _eventName( eventName )
		, _value1( "" )
		, _value2( "" )
	{

	}

	ScriptEvent( const std::string eventName, const std::string value1 )
		: _eventName( eventName )
		, _value1( value1 )
		, _value2( "" )
	{

	}

	ScriptEvent( const std::string eventName, const int value1 )
		: _eventName( eventName )
		, _value2( "" )
	{
		std::stringstream val1;
		val1 << value1;
		_value1 = val1.str( );
	}

	ScriptEvent( const std::string eventName, const std::string value1, const std::string value2 )
		: _eventName( eventName )
		, _value1( value1 )
		, _value2( value2 )
	{

	}

	ScriptEvent( const std::string eventName, const int value1, const std::string value2 )
		: _eventName( eventName )
		, _value2( value2 )
	{
		std::stringstream val1;
		val1 << value1;
		_value1 = val1.str( );
	}

	ScriptEvent( const std::string eventName, const std::string value1, const int value2 )
		: _eventName( eventName )
		, _value1( value1 )
	{
		std::stringstream val2;
		val2 << value2;
		_value2 = val2.str( );
	}

	ScriptEvent( const std::string eventName, const int value1, const int value2 )
		: _eventName( eventName )
	{
		std::stringstream val1;
		val1 << value1;
		_value1 = val1.str( );

		std::stringstream val2;
		val2 << value2;
		_value2 = val2.str( );
	}

	/*! Returns the name of the event being passed to the Script */
	inline std::string GetEventName( ) { return _eventName; };

	/*! Returns the first value passed to the script */
	inline const std::string GetValue1( ) { return _value1; };

	/*! Returns the second value passed to the script */
	inline const std::string GetValue2( ) { return _value2; };

	/*! OBSOLETE */
	/*! Gets the Type of the Event */
	inline Events::EventType GetEventType( ) const { return Events::ALL_EVENTS; };

	/*! Returns Event Data attached to the event */
	inline Events::IEventData* GetEventData( ) const { return 0; };

private:

	std::string _eventName;
	std::string _value1;
	std::string _value2;

	ScriptEvent( ) { };
	ScriptEvent( const ScriptEvent & copy ) { };
	ScriptEvent & operator = ( const ScriptEvent & copy ) { return *this; };

};

#endif
