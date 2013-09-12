/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __SPARK_UTILITIES_H
#define __SPARK_UTILITIES_H

#include "main.h"

#define SPARK_BUF_LEN				600

//#define BYTE_N(x,n)					(((x) >> n*8) & 0x000000FF)

//#define SPARK_SERVER_IP				"54.235.79.249" /* HARDCODED in SPARK_UTILITIES.C */
#define SPARK_SERVER_PORT			5683

#define USER_VAR_MAX_COUNT			10
#define USER_VAR_KEY_LENGTH			12

#define USER_FUNC_MAX_COUNT			10
#define USER_FUNC_KEY_LENGTH		12
#define USER_FUNC_ARG_LENGTH		256

typedef enum
{
	SLEEP_MODE_WLAN = 0, SLEEP_MODE_PEPH = 1, SLEEP_MODE_DEEP = 2
} Spark_Sleep_TypeDef;

typedef enum
{
	BOOLEAN = 1, INT = 2, STRING = 4, DOUBLE = 9
} Spark_Data_TypeDef;

typedef struct Spark_Namespace {
	void (*variable)(const char *, void *, Spark_Data_TypeDef);
	void (*function)(const char *, int (*)(char *));
	void (*event)(char *, char *);
	void (*sleep)(Spark_Sleep_TypeDef, long);
	bool (*connected)(void);
	int (*connect)(void);
	int (*disconnect)(void);
} Spark_Namespace;

void Spark_Variable(const char *varKey, void *userVar, Spark_Data_TypeDef userVarType);
void Spark_Function(const char *funcKey, int (*pFunc)(char *paramString));
void Spark_Event(char *eventName, char *eventResult);
void Spark_Sleep(Spark_Sleep_TypeDef sleepMode, long seconds);
bool Spark_Connected(void);
int Spark_Connect(void);
int Spark_Disconnect(void);
int Spark_Process_API_Response(void);

int Spark_Continue_Handshake(void);
void Spark_Handshake_Next(void);


bool userVarSchedule(const char *varKey, unsigned char token);
void userVarReturn(void);

bool userFuncSchedule(const char *funcKey, unsigned char token, const char *paramString);
void userFuncExecute(void);

void sendMessage(char *message);

//let the core know we're expecting a certain size message.
void receive_chunk(int size);

int Spark_Send_Device_Message(long socket, char * cmd, char * cmdparam, char * cmdvalue);
//void sendMessageWithData(char *message, char *data, long size);

//void handleMessage(void) __attribute__ ((weak, alias ("Default_Handler")));
char handleMessage(char *user_arg) __attribute__ ((weak));
void setup() __attribute__ ((weak));
void loop() __attribute__ ((weak));

extern void (*pHandleMessage)(void);

#endif  /* __SPARK_UTILITIES_H */
