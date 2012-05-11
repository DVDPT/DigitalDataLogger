using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using DigitalDataLogger.Devices;
using libMPSSEWrapper.Types;

namespace DigitalDataLogger
{
    internal class Program
    {

        private const int ConnectionSpeed = 2000; // Hz
        private const int LatencyTimer = 255; // Hz

        private static void Main(string[] args)
        {

            var adcSpiConfig = new FtChannelConfig
                                   {
                                       ClockRate = ConnectionSpeed,
                                       LatencyTimer = LatencyTimer,
                                       configOptions =
                                           FtConfigOptions.Mode0 | FtConfigOptions.CsDbus3 | FtConfigOptions.CsActivelow
                                   };



            var adcConfig = new Maxim186Configuration
                                {
                                    Channel = Maxim186.Channel.Channel0,
                                    ConversionType = Maxim186.ConversionType.SingleEnded,
                                    Polarity = Maxim186.Polarity.Unipolar,
                                    PowerMode = Maxim186.PowerMode.InternalClockMode
                                };

            var adc = new Maxim186(adcConfig, adcSpiConfig);

            do
            {

                int val = adc.GetConvertedSample();
                Console.WriteLine(val);
                val = adc.GetConvertedSampleFrom(Maxim186.Channel.Channel1);

            } while (true);
        }
    }
}
