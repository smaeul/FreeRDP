
#include <stdio.h>
#include <winpr/crt.h>
#include <winpr/winpr.h>
#include <winpr/tchar.h>
#include <winpr/dsparse.h>

static BOOL test_DsMakeSpnA(void)
{
	LPCSTR testServiceClass = "HTTP";
	LPCSTR testServiceName = "LAB1-W2K8R2-GW.lab1.awake.local";
	LPCSTR testSpn = "HTTP/LAB1-W2K8R2-GW.lab1.awake.local";
	BOOL rc = FALSE;
	CHAR Spn[100] = { 0 };
	DWORD status;
	DWORD SpnLength = -1;

	status = DsMakeSpnA(testServiceClass, testServiceName, NULL, 0, NULL, &SpnLength, NULL);

	if (status != ERROR_INVALID_PARAMETER)
	{
		printf("DsMakeSpnA: expected ERROR_INVALID_PARAMETER\n");
		goto fail;
	}

	SpnLength = 0;
	status = DsMakeSpnA(testServiceClass, testServiceName, NULL, 0, NULL, &SpnLength, NULL);

	if (status != ERROR_BUFFER_OVERFLOW)
	{
		printf("DsMakeSpnA: expected ERROR_BUFFER_OVERFLOW\n");
		goto fail;
	}

	if (SpnLength != 37)
	{
		printf("DsMakeSpnA: SpnLength mismatch: Actual: %" PRIu32 ", Expected: 37\n", SpnLength);
		goto fail;
	}

	status = DsMakeSpnA(testServiceClass, testServiceName, NULL, 0, NULL, &SpnLength, Spn);

	if (status != ERROR_SUCCESS)
	{
		printf("DsMakeSpnA: expected ERROR_SUCCESS\n");
		goto fail;
	}

	if (strcmp(Spn, testSpn) != 0)
	{
		printf("DsMakeSpnA: SPN mismatch: Actual: %s, Expected: %s\n", Spn, testSpn);
		goto fail;
	}

	printf("DsMakeSpnA: %s\n", Spn);
	rc = TRUE;
fail:
	return rc;
}

static BOOL test_DsMakeSpnW(void)
{
	BYTE testServiceClassW[] = { 'H', 0, 'T', 0, 'T', 0, 'P', 0, '\0', 0 };
	BYTE testServiceNameW[] = { 'L', 0, 'A', 0, 'B', 0, '1', 0, '-', 0, 'W', 0, '2', 0, 'K', 0,
				    '8', 0, 'R', 0, '2', 0, '-', 0, 'G', 0, 'W', 0, '.', 0, 'l', 0,
				    'a', 0, 'b', 0, '1', 0, '.', 0, 'a', 0, 'w', 0, 'a', 0, 'k', 0,
				    'e', 0, '.', 0, 'l', 0, 'o', 0, 'c', 0, 'a', 0, 'l', 0, 0, 0 };
	BYTE testSpnW[] = { 'H', 0, 'T', 0, 'T', 0, 'P', 0, '/', 0, 'L', 0, 'A', 0, 'B', 0, '1', 0,
			    '-', 0, 'W', 0, '2', 0, 'K', 0, '8', 0, 'R', 0, '2', 0, '-', 0, 'G', 0,
			    'W', 0, '.', 0, 'l', 0, 'a', 0, 'b', 0, '1', 0, '.', 0, 'a', 0, 'w', 0,
			    'a', 0, 'k', 0, 'e', 0, '.', 0, 'l', 0, 'o', 0, 'c', 0, 'a', 0, 'l', 0,
			    0, 0 };
	WCHAR *testServiceClass = (WCHAR *)testServiceClassW;
	WCHAR *testServiceName = (WCHAR *)testServiceNameW;
	WCHAR *testSpn = (WCHAR *)testSpnW;
	BOOL rc = FALSE;
	WCHAR Spn[100] = { 0 };
	DWORD status;
	DWORD SpnLength = -1;

	status = DsMakeSpnW(testServiceClass, testServiceName, NULL, 0, NULL, &SpnLength, NULL);

	if (status != ERROR_INVALID_PARAMETER)
	{
		printf("DsMakeSpnW: expected ERROR_INVALID_PARAMETER\n");
		goto fail;
	}

	SpnLength = 0;
	status = DsMakeSpnW(testServiceClass, testServiceName, NULL, 0, NULL, &SpnLength, NULL);

	if (status != ERROR_BUFFER_OVERFLOW)
	{
		printf("DsMakeSpnW: expected ERROR_BUFFER_OVERFLOW\n");
		goto fail;
	}

	if (SpnLength != 37)
	{
		printf("DsMakeSpnW: SpnLength mismatch: Actual: %" PRIu32 ", Expected: 37\n", SpnLength);
		goto fail;
	}

	status = DsMakeSpnW(testServiceClass, testServiceName, NULL, 0, NULL, &SpnLength, Spn);

	if (status != ERROR_SUCCESS)
	{
		printf("DsMakeSpnW: expected ERROR_SUCCESS\n");
		goto fail;
	}

	if (_wcscmp(Spn, testSpn) != 0)
	{
		char buffer1[8192];
		char buffer2[8192];
		char* SpnA = buffer1;
		char* testSpnA = buffer2;
		ConvertFromUnicode(CP_UTF8, 0, Spn, -1, &SpnA, sizeof(SpnA), NULL, NULL);
		ConvertFromUnicode(CP_UTF8, 0, testSpn, -1, &testSpnA, sizeof(testSpnA), NULL, NULL);
		printf("DsMakeSpnW: SPN mismatch: Actual: %s, Expected: %s\n", SpnA, testSpnA);
		goto fail;
	}

	{
		char buffer[8192];
		char* SpnA = buffer;
		ConvertFromUnicode(CP_UTF8, 0, Spn, -1, &SpnA, sizeof(SpnA), NULL, NULL);
		printf("DsMakeSpnW: %s\n", SpnA);
	}

	rc = TRUE;
fail:
	return rc;
}
int TestDsMakeSpn(int argc, char* argv[])
{
	WINPR_UNUSED(argc);
	WINPR_UNUSED(argv);

	if (!test_DsMakeSpnA())
		return -1;
	if (!test_DsMakeSpnW())
		return -2;
	return 0;
}
