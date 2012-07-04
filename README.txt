Hi

This is what I have done with the files you gave me:

made modifications to:
	MilkMock.h
	MilkInterface.h
to communicate with the a server running locally
(I think you can see the modifications easily or I can list them)

I have run the test with a running powersupply and received replies, although the tests have not passed except for the "test_RUNNING_state".

Now to test the program:
	run the file server2.out in a terminal.
	Then "make test" in another terminal.

	The Unit test tries to send and receieve data, and the tests file as the data is not correct.


So, the target is to run the unit test, so all the tests are passed, communicating with the Power supply.
The Unit Test has to be modified, so that all parameters of the Power Supply are completeley tested.

Regards
Lakshmana Vuppu
Caylar
Lakshmun@gmail.com

