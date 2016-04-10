using System; 
using System.Collections; 
using System.IO; 
using System.Text;

namespace sha1csharp
{
    public class Program
    { 
        //  state variables 
        private static UInt32 Message_Digest1      = 0x67452301;
        private static UInt32 Message_Digest2      = 0xEFCDAB89;
        private static UInt32 Message_Digest3      = 0x98BADCFE;
        private static UInt32 Message_Digest4      = 0x10325476;
        private static UInt32 Message_Digest5      = 0xC3D2E1F0;

        private static UInt32 SHA1CircularShift(int bits,UInt32 word) 
        {
            return ((word << bits) & 0xFFFFFFFF) | (word) >> (32-(bits));
        }

        private static void SHA1_Init()
        { 
            Message_Digest1      = 0x67452301;
            Message_Digest2      = 0xEFCDAB89;
            Message_Digest3      = 0x98BADCFE;
            Message_Digest4      = 0x10325476;
            Message_Digest5      = 0xC3D2E1F0;
        } 

        private static UInt32[] SHA1_Append(byte[] input)
        { 
            int zeros=0; 
            int ones =1; 
            int size=0; 
            int n = input.Length; 
            int m = n%64; 
            if( m < 56 )
            { 
                zeros = 55-m; 
                size=n-m+64; 
            } 
            else if (m==56)
            { 
                zeros = 63; 
                ones = 1; 
                size=n+8+64; 
            } 
            else
            { 
                zeros = 63-m+56; 
                size=n+64-m+64; 
            } 

            ArrayList bs = new ArrayList(input); 
            if(ones==1)
            { 
                bs.Add( (byte)0x80 ); // 0x80 = 10000000 
            } 
            for(int i=0;i<zeros;i++)
            { 
                bs.Add( (byte)0 ); 
            } 

            UInt64 N = (UInt64) n * 8; 
            byte h8=(byte)(N&0xFF); 
            byte h7=(byte)((N>>8)&0xFF); 
            byte h6=(byte)((N>>16)&0xFF); 
            byte h5=(byte)((N>>24)&0xFF); 
            byte h4=(byte)((N>>32)&0xFF); 
            byte h3=(byte)((N>>40)&0xFF); 
            byte h2=(byte)((N>>48)&0xFF); 
            byte h1=(byte)(N>>56); 
            bs.Add(h1); 
            bs.Add(h2); 
            bs.Add(h3); 
            bs.Add(h4); 
            bs.Add(h5); 
            bs.Add(h6); 
            bs.Add(h7); 
            bs.Add(h8); 
            byte[] ts=(byte[])bs.ToArray(typeof(byte)); 

            /* Decodes input (byte[]) into output (UInt32[]). Assumes len is 
             * a multiple of 4. 
             */ 
            UInt32[] output = new UInt32[size/4]; 
            for(Int64 i=0,j=0;i<size;j++,i+=4)
            {
                UInt32 temp = 0;
                temp=temp|(((UInt32)ts[i])<<24);
                temp=temp|(((UInt32)ts[i+1])<<16);
                temp=temp|(((UInt32)ts[i+2])<<8);
                temp=temp|(((UInt32)ts[i+3]));
                output[j] = temp;
            } 
            return output; 
        } 
        private static UInt32[] SHA1_Transform(UInt32[] x)
        { 
            SHA1_Init();

            UInt32[] K = {
                             0x5A827999,
                             0x6ED9EBA1,
                             0x8F1BBCDC,
                             0xCA62C1D6
                         };
            int         t;                  
            UInt32    temp;              
            UInt32[]    W = new UInt32[80];             
            UInt32    A, B, C, D, E;   

            for(int k=0; k<x.Length; k+=16)
            {
                for(t = 0; t < 16; t++)
                {
                    W[t] = x[t+k];
                }

                for(t = 16; t < 80; t++)
                {
                    W[t] = SHA1CircularShift(1,W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16]);
                }

                A = Message_Digest1;
                B = Message_Digest2;
                C = Message_Digest3;
                D = Message_Digest4;
                E = Message_Digest5;

                for(t = 0; t < 20; t++)
                {
                    temp =  SHA1CircularShift(5,A) +
                        ((B & C) | ((~B) & D)) + E + W[t] + K[0];
                    temp &= 0xFFFFFFFF;
                    E = D;
                    D = C;
                    C = SHA1CircularShift(30,B);
                    B = A;
                    A = temp;
                }

                for(t = 20; t < 40; t++)
                {
                    temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[1];
                    temp &= 0xFFFFFFFF;
                    E = D;
                    D = C;
                    C = SHA1CircularShift(30,B);
                    B = A;
                    A = temp;
                }

                for(t = 40; t < 60; t++)
                {
                    temp = SHA1CircularShift(5,A) +
                        ((B & C) | (B & D) | (C & D)) + E + W[t] + K[2];
                    temp &= 0xFFFFFFFF;
                    E = D;
                    D = C;
                    C = SHA1CircularShift(30,B);
                    B = A;
                    A = temp;
                }

                for(t = 60; t < 80; t++)
                {
                    temp = SHA1CircularShift(5,A) + (B ^ C ^ D) + E + W[t] + K[3];
                    temp &= 0xFFFFFFFF;
                    E = D;
                    D = C;
                    C = SHA1CircularShift(30,B);
                    B = A;
                    A = temp;
                }

                Message_Digest1 = (Message_Digest1 + A) & 0xFFFFFFFF;
                Message_Digest2 = (Message_Digest2 + B) & 0xFFFFFFFF;
                Message_Digest3 = (Message_Digest3 + C) & 0xFFFFFFFF;
                Message_Digest4 = (Message_Digest4 + D) & 0xFFFFFFFF;
                Message_Digest5 = (Message_Digest5 + E) & 0xFFFFFFFF;
            }
        
            return new UInt32[]{Message_Digest1,Message_Digest2,Message_Digest3,Message_Digest4,Message_Digest5}; 
        } 
        public static string SHA1Array(UInt32[] input)
        { 
            StringBuilder sb = new StringBuilder();

            for(int i=0; i<input.Length; i++)
            {
                sb.Append( String.Format("{0:X8}", input[i]).ToUpper() );
            }

            return sb.ToString(); 
        } 

        public static string MySHA1String(string message)
        { 
            char[] c = message.ToCharArray(); 
            byte[] b = new byte[c.Length]; 
            for(int i=0;i<c.Length;i++)
            { 
                b[i]=(byte)c[i]; 
            } 
            UInt32[] output = SHA1_Append( b );
            UInt32[] str = SHA1_Transform( output );
            return SHA1Array(str);
            
        } 
        public static string MySHA1File(string fileName)
        { 
            FileStream fs=File.Open(fileName,FileMode.Open,FileAccess.Read); 
            byte[] array=new byte[fs.Length]; 
            fs.Read(array,0,(int)fs.Length); 
            fs.Close(); 
            UInt32[] output = SHA1_Append( array );
            UInt32[] str = SHA1_Transform( output );
            return SHA1Array(str);
        } 
        #region Unit Test
        public static string Test(string message)
        { 
            return "\r\nSHA1 (\""+message+"\") = " + MySHA1String(message); 
        } 
        public static string TestSuite()
        {     
            string s = ""; 
            s+=Test("abcaasdfdgetnhtdhbndfgvbgvgervgbvev befregvevrefgwrdsaaa"); 
            s+=Test("a"); 
            s+=Test("abc"); 
            s+=Test("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq"); 
            s+=Test("abcdefghijklmnopqrstuvwxyz"); 
            s+=Test("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789"); 
            s+=Test("abcaasdfdgetnhtdhbndfgvbgvgervgbvev befregvevrefgwrdsxwxwxwxwx"); 
            //        StringBuilder sb = new StringBuilder();
            //        for(int i=0; i<1000000; i++)
            //            sb.Append("a");
            //        s+=Test(sb.ToString());

            return s;     
        } 

        public static void Main()
        {
            Console.WriteLine(Program.TestSuite());
            Console.ReadLine();
        }
        #endregion
    } 
}
