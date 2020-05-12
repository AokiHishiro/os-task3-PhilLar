#include "lab3.h"
#include <windows.h> 

//
// lab3 code should be located here!
//

// number of threads: 10

//init mutex
HANDLE muLock;

// init semaphores
HANDLE semStart;
// semaphores for sequential threads
HANDLE semGI, semIH, semHG, semHalfG;

HANDLE threads[10];
DWORD thread_id;


unsigned int lab3_thread_graph_id() 
{
    return 12;
}

const char* lab3_unsynchronized_threads()
{
    return "defg";
}

const char* lab3_sequential_threads()
{
    return "ghi";
}


DWORD WINAPI thread_a(LPVOID) {
    WaitForSingleObject(semStart, INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'a' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    return TRUE;
}

DWORD WINAPI thread_b(LPVOID) {
    WaitForSingleObject(threads[0], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'b' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    return TRUE;
}

DWORD WINAPI thread_c(LPVOID) {
    WaitForSingleObject(threads[0], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'c' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    return TRUE;
}

DWORD WINAPI thread_d(LPVOID) {
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'd' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    return TRUE;
}

DWORD WINAPI thread_e(LPVOID) {
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'e' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    return TRUE;
}

DWORD WINAPI thread_f(LPVOID) {
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'f' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }


    return TRUE;
}

DWORD WINAPI thread_g(LPVOID) {
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'g' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    ReleaseSemaphore(semHalfG, 1, NULL);
    ReleaseSemaphore(semHalfG, 1, NULL);

    WaitForSingleObject(threads[3], INFINITE);
    WaitForSingleObject(threads[4], INFINITE);
    WaitForSingleObject(threads[5], INFINITE);
    // HANDLE semGI, semIH, semHG;
    for (int i=0; i<4; i++) {
        WaitForSingleObject(semHG, INFINITE);
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'g' << std::flush;
        ReleaseMutex(muLock);
        computation();
        ReleaseSemaphore(semGI, 1, NULL);
    }
    return TRUE;
}

DWORD WINAPI thread_i(LPVOID) {
    WaitForSingleObject(threads[3], INFINITE);
    WaitForSingleObject(threads[4], INFINITE);
    WaitForSingleObject(threads[5], INFINITE);
    WaitForSingleObject(semHalfG, INFINITE);
    // HANDLE semGI, semIH, semHG;
    for (int i=0; i<4; i++) {
        WaitForSingleObject(semGI, INFINITE);
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'i' << std::flush;
        ReleaseMutex(muLock);
        computation();
        ReleaseSemaphore(semIH, 1, NULL);
    }

    return TRUE;
}

DWORD WINAPI thread_h(LPVOID) {
    WaitForSingleObject(threads[3], INFINITE);
    WaitForSingleObject(threads[4], INFINITE);
    WaitForSingleObject(threads[5], INFINITE);
    WaitForSingleObject(semHalfG, INFINITE);
    // HANDLE semGI, semIH, semHG;
    for (int i=0; i<4; i++) {
        WaitForSingleObject(semIH, INFINITE);
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'h' << std::flush;
        ReleaseMutex(muLock);
        computation();
        ReleaseSemaphore(semHG, 1, NULL);
    }

    return TRUE;
}

DWORD WINAPI thread_k(LPVOID) {
    WaitForSingleObject(threads[8], INFINITE);
    WaitForSingleObject(threads[7], INFINITE);
    WaitForSingleObject(threads[6], INFINITE);
    for (int i=0; i<4; i++) {
        WaitForSingleObject(muLock, INFINITE);
        std::cout << 'k' << std::flush;
        ReleaseMutex(muLock);
        computation();
    }

    return TRUE;
}



int lab3_init()
{

    muLock = CreateMutex(NULL, FALSE, NULL);
	if (muLock == NULL) {
		std::cerr << "CreateMutex error: " << GetLastError() << '\n';
		return 1;
	}
// HANDLE semI, semK, semA, sems[1], sems[2], sems[3], sems[4], sems[5], semG, semH;
    semStart = CreateSemaphore(NULL, 1, 6, NULL);
	if (semStart == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

    semHalfG = CreateSemaphore(NULL, 0, 6, NULL);
	if (semHalfG == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}

    semHG = CreateSemaphore(NULL, 1, 6, NULL);
	if (semHG == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
    semIH = CreateSemaphore(NULL, 0, 6, NULL);
	if (semIH == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}
    semGI = CreateSemaphore(NULL, 0, 6, NULL);
	if (semGI == NULL) {
		std::cerr << "CreateSemaphore error: " << GetLastError() << '\n'; return 1;
	}


    
    threads[0] = CreateThread(NULL, 0, thread_a, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[1] = CreateThread(NULL, 0, thread_b, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[2] = CreateThread(NULL, 0, thread_c, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    WaitForSingleObject(threads[1], INFINITE);
    WaitForSingleObject(threads[2], INFINITE);
    threads[3] = CreateThread(NULL, 0, thread_d, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[4] = CreateThread(NULL, 0, thread_e, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[5] = CreateThread(NULL, 0, thread_f, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[6] = CreateThread(NULL, 0, thread_g, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[7] = CreateThread(NULL, 0, thread_h, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[8] = CreateThread(NULL, 0, thread_i, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}
    threads[9] = CreateThread(NULL, 0, thread_k, NULL, 0, &thread_id);
	if (threads[0] == NULL) {
		std::cerr << "CreateThread error: " << GetLastError() << '\n'; return 1;
	}

    WaitForMultipleObjects(10, threads, TRUE, INFINITE);

    CloseHandle(semStart);
    CloseHandle(semHG);
    CloseHandle(semIH);
    CloseHandle(semGI);
    CloseHandle(semHalfG);
             
    for (int i = 0; i < 10; i++) {
        CloseHandle(threads[i]);
    }
            
    
    
    return 0;
}


