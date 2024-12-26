#pragma once

#ifdef _DLLBUILD
#define DllExport   __declspec( dllexport )
#else
#define DllExport 
#endif

#define APPLOGGER_EXIT_ERROR           -1
#define APPLOGGER_EXIT_SUCCESS         0
#define APPLOGGER_EXIT_WITH_MESSAGES   1

#if __cplusplus
extern "C" {
#endif

   /**
    * @brief Retrieves the applogger errors to be displayed or 
    * used by the caller.
    * 
    * When this is called without NULL for buffer, the message queue
    * is emptied.
    * 
    * @param buffer [out] Returns the string containing all current messages from the module. It can be NULL to get the required size of the buffer.
    * @param nchars [inout] The size of the buffer. If it is smaller than the required length, the message is truncated.
    * @param err [out] Returns 0 on success, and -1 on error.
    */
   DllExport void get_applogger_errors(char* buffer, int* nchars, int* err);

   /**
    * @brief Retrieves the applogger's module version.
    * 
    * @param buffer [out] Returns the string containing the version info for the module. It can be NULL to get the required size of the buffer.
    * @param nchars [inout] The size of the buffer. If it is smaller than the required length, the message is truncated.
    * @param err [out] Returns 0 on success, and -1 on error.
    */
   DllExport void get_applogger_version(char* buffer, int* nchars, int* err);

   /**
    * @brief Initialises the applogger module.
    * 
    * @param err [out] Returns 0 on success, -1 on error and 1 in case of success with messages.
    */
   DllExport void initialise_applogger(int* err);

   /**
    * @brief Adds a sink (file or stream) to the logger.
    * 
    * @param sinkname [in] The path and file name for the log.
    * @param channel [in] The name of the channel associated with the sink (log file).
    * @param format [in] Custom format of the error messages for this sink/channel.
    * @param minseverity [in] The minimum level of severity of a message to appear in this log. Valid values are [Debug, Info, Warning, Error, Critical] (not case-sensitive). It can be NULL and it defaults to Info.
    * @param err [out] Returns 0 on success, -1 on error and 1 in case of success with messages.
    */
   DllExport void add_sink_to_applogger(const char* sinkname, 
      const char* channel, const char* format, const char* minseverity, int* err);

   /**
    * @brief Sends a message to the logger to be logged to the appropriate sink.
    * 
    * @param channel [in] The name of channel where the message is coming from. It can be NULL in which case the message will be written as if it was coming from all channels.
    * @param severity [in] The severity of the message. Valid values are [Debug, Info, Warning, Error, Critical] (not case-sensitive). It can be NULL and it defaults to Info.
    * @param message [in] The message to be logged.
    * @param err [out] Returns 0 on success, -1 on error and 1 in case of success with messages.
    */
   DllExport void send_message_to_applogger(const char* channel, const char* severity, const char* message, int*err);

#if __cplusplus
}
#endif 

