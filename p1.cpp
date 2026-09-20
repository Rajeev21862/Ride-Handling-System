#include<iostream>
using namespace std;
int main(){
    system("color 3A ");
    int quant;
    int choice;
    //quantity
    int Qrooms=0,Qpasta=0,Qburger=0,Qnoodles=0,Qshake=0;
    //food items sold
    int Srooms=0,Spasta=0,Sburger=0,Snoodles=0,Sshake=0;
    //total price of items
    int total_rooms=0,total_pasta=0,total_burger=0,total_noodles=0,total_shake=0;
    
    cout<<"\n\t Quantity of items we have";
    cout<<"\n Rooms available:";
    cin>>Qrooms;
    cout<<"\n Quantity of pasta :";
    cin>>Qpasta;
    cout<<"\n Quantity of burger :";
    cin>>Qburger;
    cout<<"\n Quantity of noodles :";
    cin>>Qnoodles;
    cout<<"\n Quantity of pshake :";
    cin>>Qshake;
   

    m:
    cout<<"\n\t\t\t Please select frorm the menu options";
    cout<<"\n\n1) rooms";
    cout<<"\n\n2) pasta ";
    cout<<"\n\n3) burger";
    cout<<"\n\n4) noodles";
    cout<<"\n\n5) shake";
    cout<<"\n\n6) Information regarding sales and collection";
    cout<<"\n\n7  Exit";

    cout<<"\n\n Please Enter your choice!";
    cin>>choice;

    switch (choice)
    {
    case 1:
        cout<<"\n\n Enter the number of rooms you want:";
        cin>>quant;
        if(Qrooms-Srooms>=quant)
        {
            Srooms=Srooms+quant;
            total_rooms=total_rooms+quant*1200;
            cout<<"\n\n\t\t"<<quant<<"room/rooms have been alloted to you!";

        }
        else{
            cout<<"\n\t only"<<Qrooms-Srooms<<"rooms remaining in hotel";
            break;
        }

    case 2:
        cout<<"\n\n Enter  pasta Quantity:";
        cin>>quant;
        if(Qpasta-Spasta>=quant)
        {
            Spasta=Spasta+quant;
            total_pasta=total_pasta+quant*250;
            cout<<"\n\n\t\t"<<quant<<"pasta is the order!";

        }
        else{
            cout<<"\n\t only"<<Qpasta-Spasta<<"pasta remaining in hotel";
            break;
        }

    case 3:
        cout<<"\n\n Enter burger Quantity:";
        cin>>quant;
        if(Qburger-Sburger>=quant)
        {
            Sburger=Sburger+quant;
            total_burger=total_burger+quant*120;
            cout<<"\n\n\t\t"<<quant<<"burger is the order!";

        }
        else{
            cout<<"\n\t only"<<Qburger-Sburger<<"burger remaining in hotel";
            break;
        }

    case 4:
        cout<<"\n\n Enter  noodle Quantity:";
        cin>>quant;
        if(Qnoodles-Snoodles>=quant)
        {
            Spasta=Snoodles+quant;
            total_noodles=total_noodles+quant*140;
            cout<<"\n\n\t\t"<<quant<<"noodles is the order!";

        }
        else{
            cout<<"\n\t only"<<Qnoodles-Snoodles<<"noodles remaining in hotel";
            break;
        }
        
    case 5:
        cout<<"\n\n Enter  shake Quantity:";
        cin>>quant;
        if(Qshake-Sshake>=quant)
        {
            Sshake=Sshake+quant;
            total_shake=total_shake+quant*120;
            cout<<"\n\n\t\t"<<quant<<"shake is the order!";

        }
        else{
            cout<<"\n\t only"<<Qshake-Sshake<<"shake remaining in hotel";
            break;
        }
    case 6:
        cout<<"\n\t Details of sles and collection:";
        cout<<"\n\n Number of rooms we had:"<<Qrooms;
        cout<<"\n\t Number of rooms we gave for rent:"<<Srooms;
        cout<<"\n\t Remaining rooms"<<Qrooms-Srooms;
        cout<<"\n\t Total rooms collection for the day :"<<total_rooms;

        cout<<"\n\n Number of patasa we had:"<<Qpasta;
        cout<<"\n\t Number of pastas we sold :"<<Spasta;
        cout<<"\n\t Remaining pastas"<<Qpasta-Spasta;
        cout<<"\n\t Total pastas collection for the day :"<<total_pasta;

        cout<<"\n\n Number of burger we had:"<<Qburger;
        cout<<"\n\t Number of burger we sold:"<<Sburger;
        cout<<"\n\t Remaining burger"<<Qburger-Sburger;
        cout<<"\n\t Total burger collection for the day :"<<total_burger;

        cout<<"\n\n Number of noodles we had:"<<Qnoodles;
        cout<<"\n\t Number of noodles we sold:"<<Snoodles;
        cout<<"\n\t Remaining noodles"<<Qnoodles-Snoodles;
        cout<<"\n\t Total noodles collection for the day :"<<total_noodles;    

        cout<<"\n\n Number of shake we had:"<<Qshake;
        cout<<"\n\t Number of shake we sold:"<<Sshake;
        cout<<"\n\t Remaining shake"<<Qshake-Sshake;
        cout<<"\n\t Total shake collection for the day :"<<total_shake;         
        cout<<"\n\n\n total collection for the day:"<<total_rooms+total_pasta+total_burger+total_noodles+total_shake;
        break;
    case 7: 
        exit(0);

    default:
        cout<<"\n Please select the numbers mentioned above!";
    }
    goto m;
}