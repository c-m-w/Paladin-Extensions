/// Connectivity.hpp

#pragma once

namespace PX
{
	namespace Net
	{
		/** \brief Base site address. */
		PX_SDK const std::string strSite = PX_XOR( "https://paladin.rip" );

		/** \brief Pointer where the connection information is stored. */
		PX_SDK CURL* pConnection = nullptr;

		/** \brief Formats passed post data into a string that can be used as post data in a connection. */
		/**	\param dqPostData All of the elements that are to be included in the formatted data. */
		/**	\return Formatted post data string. */
		std::string PX_API GeneratePostData( const std::deque< Types::post_data_t >& dqPostData );
		/** \brief Attempts to initialize cURL. */
		/**	\return true - Initialization was successful.\n false - Initialization was not successful. */
		bool PX_API InitializeConnection( );
		/** \brief Shuts cURL down to clean up the connection pointer.\n Call this when you are done doing anything with connectivity. */
		void PX_API CleanupConnection( );
		/** \brief Makes a request to a site. */
		/**	\param strSite Site to make the request to.	*/
		/** \param dqPostData Post data to send to the site. */
		/**	\return What the site sends back from the request. */
		std::string PX_API Request( const std::string& strSite, const std::deque< Types::post_data_t >& dqPostData );
	}
}
