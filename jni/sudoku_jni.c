/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */
//#include "first.h"
/*------- Program Header Files --------------------------*/
//#include <dlfcn.h>   /* For dynamic loading */
#include <android/log.h>

#include "sudoku_lib.h"
#include <jni.h>

#define  LOG_TAG    "sudoku_jni"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)


static void* pModule = 0;
sudoku_private_type Sudoku;
int led_state;
sudoku_handler Shandle;

sudoku_element_value element = {5,5,5};
sudoku_element_value evec[5] = {
                               {3,9,6},
                               {6,2,2},
                               {9,4,9},
                               {1,8,1},
                               {2,2,3}};
sudoku_init_vector vector;


int sudoku_startup(sudoku_handler *Shandle);
void sudoku_teardown(sudoku_handler *Shandle);

jint Java_org_example_sudoku_Buttons_add( JNIEnv*  env,
                                      jobject  this,
                                      jint     x,
                                      jint     y )
{
	//LOGI("add JNI method\n");
    return x+y;//first(x, y);
}

void Java_org_example_sudoku_Sudoku_loadLibraries( JNIEnv*  env,
                                      jobject  this)
{
		LOGI("Init loadLibraries\n");

	  /* First load sudoku library(*.so) and get handlers
       * the for sudoku functions */
  //     sudoku_startup(&Shandle);

//       LOGI("Library Loaded 02\n");

       /* supposes that the player has started */
       /* Initializes the sudoku struct, open device driver entries */
       //Shandle.sudoku_init(&Sudoku);
       //LOGI("Library Loaded\n");

	sodoku_handle(&Shandle);
	char error_log[256] = "/n";
	Shandle.sudoku_init(&Sudoku, error_log);
	LOGI("Error Log: %s", error_log);

	if(Sudoku.sDriverSupport)
			LOGI("LED or Grid Supported!!\n");

	if(!Sudoku.sDriverSupport & DRV_LED_SUDOKU_SUPPORT)
			LOGI("ERROR Led. Value of fd_sLedDriver: %d\n", Sudoku.fd_sLedDriver);

	if(!Sudoku.sDriverSupport & DRV_GRID_SUDOKU_SUPPORT)
		LOGI("ERROR Grid. Value of fd_sCommandsDriver: %d\n", Sudoku.fd_sCommandsDriver);

	LOGI("Value of fd_sLedDriver: %d. \n", Sudoku.fd_sLedDriver);
	LOGI("Value of fd_sCommandsDriver: %d\n", Sudoku.fd_sCommandsDriver);
	LOGI("Value of sDriverSupport: %d\n", Sudoku.sDriverSupport );


	LOGI("DONE\n");




}

jint Java_org_example_sudoku_Sudoku_test( JNIEnv*  env,
                                      jobject  this)
{
	LOGI("test initiated\n");
	//Get_sodoku_handle(&Shandle);
	Shandle.sudoku_set_led_on(&Sudoku);
	sleep(2);
	Shandle.sudoku_set_led_off(&Sudoku);
	/*vector.initvector = evec;
    vector.nelements = 5;

	 if (Sudoku.sDriverSupport == NO_DRV_SUPPORT)
	               LOGI(stderr, "error: NO_DRV_SUPPORT.\n");
	       else {
	               LOGI(stderr, "Success: Ready to play.\n");
	               //  Clean driver sudoku's driver grid
	               Shandle.sudoku_clean_grid(&Sudoku);
	               // Initialized sudoku's grid with predefined values
	               Sudoku.data = (void *)&vector;
	               Shandle.sudoku_init_grid(&Sudoku);
	               // Set a value into sudoku's driver grid
	               Sudoku.data = (void *)&element;
	               Shandle.sudoku_set_value(&Sudoku);

	               // Test grid throug /proc/sudoku
	               system("cat /proc/sudoku");

	               // Test Led driver
	               LOGI(stderr, "\nTesting LEDs.\n");
	               Shandle.sudoku_set_led_on(&Sudoku);
	               sleep(2);
	               Shandle.sudoku_set_led_off(&Sudoku);
	               sleep(2);
	               Shandle.sudoku_set_led_on(&Sudoku);
	               Shandle.sudoku_get_led_status(&Sudoku);
	               led_state = (int)Sudoku.data;
	               LOGI(stderr, "LED State: %d.\n", led_state);
	       }
	       // DeInitializes the sudoku struct, close device driver entries
	               // when it supposes that player has finished
	               Shandle.sudoku_deinit(&Sudoku);

	               // Unload the sudoku library
	               sudoku_teardown(&Shandle);
*/
	               return 0;


}

void Java_org_example_sudoku_Game_setLedOFF( JNIEnv*  env,
                                      jobject  this)

{
	Shandle.sudoku_set_led_off(&Sudoku);
	LOGI("LED OFF CALLED\n");

}

void Java_org_example_sudoku_PuzzleView_setLedON( JNIEnv*  env,
                                      jobject  this)

{
	int error = Shandle.sudoku_set_led_on(&Sudoku);
	LOGI("LED ON CALLED. Value: %d \n", error);
}


int sudoku_startup(sudoku_handler *Shandle)
{
/*	 LOGI("startup internal method\n");
        int (*FooPtr) (sudoku_handler *);

        char *module_name = "/system/lib/libsudoku.so";

        const char* pErr = dlerror();

  */      /* load the component and check for an error*/
    // pModule = dlopen(module_name , /*RTLD_LOCAL | RTLD_LAZY | */RTLD_NOW);
      //  if( !pModule /*== NULL */) {
       /*	LOGI("Failed because %s\n", dlerror());
                return -1;
        }
    	LOGI("DLERROR has: %s\n", dlerror());

    */    /* Get a function pointer to the "sodoku_handle" function */
     /*   FooPtr = dlsym(pModule, "Get_sodoku_handle");
        if( (pErr != NULL) ) {
            dlclose(pModule);
            pModule = NULL;
        	LOGI("Error01 Failed because %s\n", dlerror());
                     return -1;
        }

        if (FooPtr == NULL) {
						LOGI("Error02: Failed because %s\n", dlerror());
                        //pComponents[i] = NULL;
                        dlclose(pModule);
                        pModule = NULL;
                        return -1;
         }
*/
        /* We now can access the dll. So, we need to call the "sodoku_handle"
         * method to load up the "handle" (which is just a list of functions to
         * call) and we should be all set. */
        //pComponent = *Shandle;
        //(*FooPtr)(Shandle);
  /*    	 LOGI("Library loaded!\n");
*/
        return 0;
}

void sudoku_teardown(sudoku_handler *Shandle)
{
//	LOGI("teardown internal method\n");
        /* release the component and the component handle */
    /*    if (pModule)
                dlclose(pModule);
        pModule = NULL;*/
}


