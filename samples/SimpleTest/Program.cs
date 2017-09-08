using System;
using System.Collections.Generic;
using System.Text;
using JulMar.Tapi3;

namespace TestTapi
{
    class Program
    {
        static void Main(string[] args)
        {
            TTapi tapi = new JulMar.Tapi3.TTapi();
            TCall call = null; TAddress modemAddr = null;
            Console.WriteLine("{0} found", tapi.Initialize());

            tapi.TE_CALLNOTIFICATION += delegate(object sender, TapiCallNotificationEventArgs e)
            {
                Console.WriteLine("New call {0} detected from {1}", e.Call.ToString(), e.Event);
            };
            tapi.TE_CALLSTATE += delegate(object sender, TapiCallStateEventArgs e)
            {
                Console.WriteLine("{0}:{4} has changed state to {1} due to {2} - current={3}:{5}", e.Call, e.State, e.Cause, e.Call == call, e.Call.GetHashCode(), (call != null) ? call.GetHashCode() : 0);

                if (e.State == CALL_STATE.CS_INPROGRESS && e.Call == call)
                {
                    Console.WriteLine("Dropping call");
                    e.Call.Disconnect(DISCONNECT_CODE.DC_NORMAL);
                }
            };

            foreach (TPhone phone in tapi.Phones)
            {
                using (phone)
                {
                    phone.Open(PHONE_PRIVILEGE.PP_MONITOR);
                    Console.WriteLine("{0}\nTotal buttons: {1}", phone.Display, phone.get_PhoneCapability(PHONECAPS_LONG.PCL_NUMBUTTONLAMPS));
                }
            }

            foreach (TAddress addr in tapi.Addresses)
            {
                if (String.Compare(addr.ServiceProviderName, "unimdm.tsp", true) == 0 && addr.QueryMediaType(TAPIMEDIATYPES.AUDIO))
                    modemAddr = addr;
            }

            if (modemAddr != null)
            {
                Console.WriteLine("{0} = {1} ({3}) [{2}]", modemAddr.AddressName, modemAddr.State, modemAddr.ServiceProviderName, modemAddr.DialableAddress);
                modemAddr.Monitor(TAPIMEDIATYPES.AUDIO);

                ConsoleKey ki = ConsoleKey.A;
                while (ki != ConsoleKey.Q)
                {
                    // Flip the auto-destroy flag
                    if (ki == ConsoleKey.D) 
                    {
                        tapi.AutoDestroyCalls = !tapi.AutoDestroyCalls;
                        Console.WriteLine("Set AutoDestroy to {0}", tapi.AutoDestroyCalls);
                    }

                    // List existing calls
                    if (ki == ConsoleKey.L)
                    {
                        foreach (TCall _call in modemAddr.Calls)
                        {
                            Console.WriteLine("Existing call found: {0}:{1}", _call, _call.GetHashCode());
                            _call.Dispose(); // Go ahead and dump it
                        }
                    }

                    // Create a new call
                    else
                    {
                        call = modemAddr.CreateCall("5551213", LINEADDRESSTYPES.PhoneNumber, TAPIMEDIATYPES.DATAMODEM);
                        Console.WriteLine("Created new call {0}:{1}", call, call.GetHashCode());
                        try
                        {
                            // This will fail if existing call interface is still around (i.e. not disposed)
                            call.Connect(false);
                        }
                        catch (TapiException ex)
                        {
                            Console.WriteLine(ex.Message);
                        }
                    }
                    Console.WriteLine("Press a key to try another call.. Q to quit");
                    ki = Console.ReadKey().Key;
                }
            }

            tapi.Shutdown();

            // Call should be disposed here.. state will be CS_UNKNOWN    
            if (call != null)
                Console.WriteLine("{0} {1}", call, call.CallState);
         }
    }
}
