{
gROOT->SetStyle("Plain");



TFile* f1 = new TFile("2x2_G18_10a_02_11a_200k.root");
TTree *nt = (TTree *)f1->Get("gst");
Int_t nevents= nt->GetEntries();
cout<<"\n ----------N events = "<< nevents<<"\n"<<endl;
 Char_t cut1[2000];
 sprintf(cut1, "");
 Int_t nch=100;
Float_t min_x=0.0, max_x = 5;
nt->Print();

Int_t nipip;
nt->SetBranchAddress("nipip", &nipip);
Int_t nipim;
nt->SetBranchAddress("nipim", &nipim);
Int_t nipi0;
nt->SetBranchAddress("nipi0", &nipi0);
Int_t nfpi0;
nt->SetBranchAddress("nfpi0", &nfpi0);
Int_t nfpip;
nt->SetBranchAddress("nfpip", &nfpip);
Int_t nfpim;
nt->SetBranchAddress("nfpim", &nfpim);



Int_t sumnipip = 0;
Int_t sumnipim = 0;
Int_t sumnipi0 = 0;


Int_t sumnfpip = 0;
Int_t sumnfpim = 0;
Int_t sumnfpi0 = 0;


Int_t sumpi;
Int_t sumpif;


for(Int_t jj = 0; jj<=20000; jj++)
{
    nt->GetEntry(jj);
    sumnipi0 += nipi0;
    sumnipip += nipip;
    sumnipim += nipim;
    
    sumnfpi0 += nfpi0;
    sumnfpip += nfpip;
    sumnfpim += nfpim;
}
    sumpi = sumnipi0 + sumnipip + sumnipim;
    sumpif = sumnfpi0 + sumnfpip + sumnfpim;
    cout<<"\n Sum of all primary Pi particles: "<<sumpi<<endl;
    cout<<"\n Sum of all final Pi particles: "<<sumpif<<endl;


Int_t nikp;
nt->SetBranchAddress("nikp", &nikp);
Int_t nikm;
nt->SetBranchAddress("nikm", &nikm);
Int_t nik0;
nt->SetBranchAddress("nik0", &nik0);
Int_t nfkp;
nt->SetBranchAddress("nfkp", &nfkp);
Int_t nfkm;
nt->SetBranchAddress("nfkm", &nfkm);
Int_t nfk0;
nt->SetBranchAddress("nfk0", &nfk0);
Double_t Ev;
nt->SetBranchAddress("Ev", &Ev);


Int_t sumnikp = 0;
Int_t sumnikm = 0;
Int_t sumnik0 = 0;


Int_t sumnfkp = 0;
Int_t sumnfkm = 0;
Int_t sumnfk0 = 0;


Int_t sumki;
Int_t sumkf;


for(Int_t ii = 0; ii<=20000; ii++)
{
    nt->GetEntry(ii);
    sumnik0 += nik0;
    sumnikp += nikp;
    sumnikm += nikm;
    
    sumnfk0 += nfk0;
    sumnfkp += nfkp;
    sumnfkm += nfkm;
}
    sumki = sumnik0 + sumnikp + sumnikm;
    sumkf = sumnfk0 + sumnfkp + sumnfkm;
    cout<<"\n Sum of all primary K particles: "<<sumki<<endl;
    cout<<"\n Sum of all final K particles: "<<sumkf<<endl;



//>>>>>>>>>>>>


vector<double> vratiof;
vector<double> vratio;

for(Int_t j=0; j<=1000;j++) // заповнення вектору відношення фінальної кількості частинок
{
  nt->GetEntry(j);
  Double_t numf = nfpip + nfpim + nfpi0;
  Double_t denomf = nfkp + nfkm + nfk0;
  if (denomf>0)
  {
    vratiof.push_back(numf/denomf);
  }
  else{
    // do nothing
  }
  vratiof.erase(std::remove(vratiof.begin(), vratiof.end(), 0), vratiof.end()); // видалення всіх нулів з вектору
}

for(Int_t u=0; u<=1000;u++) // заповнення вектору відношення фінальної кількості частинок
{
  nt->GetEntry(u);
  Double_t num = nipip + nipim + nipi0;
  Double_t denom = nikp + nikm + nik0;
  if (denom>0)
  {
    vratio.push_back(num/denom);
  }
  else{
    // do nothing
  }
  vratio.erase(std::remove(vratio.begin(), vratio.end(), 0), vratio.end()); // видалення всіх нулів з вектору
}



Double_t *ratiof, sizef; // створення масиву відношення кінцевого з змінним розміром
sizef = vratiof.size();
ratiof = new Double_t [sizef];
for(Int_t i=0; i<= vratiof.size(); i++)
{
  ratiof[i]=vratiof[i]; // заповнення масиву кінцевого з відфільтрованого кінцевого вектору
}

//const int arsize = array_size.size();
Double_t *ratio, sizei; // створення масиву відношення з змінним розміром
sizei = vratio.size();
ratio = new Double_t [sizei];
for(Int_t i=0; i<=vratio.size();i++)
{
    ratio[i] = vratio[i]; // заповнення масиву з відфільтрованого вектору
}



//>>>>>>
Double_t Energy[50];
//Double_t *energy1, energy1size;
//energy1size = vratio.size();
//energy1 = new Double_t[energy1size];

for(Int_t i=0; i<=vratio.size(); i++)
{
  nt->GetEntry(i);
  //energy1[i]=Ev;
  Energy[i]=Ev;
}

TCanvas *mk1 = new TCanvas("mk1", "Pi to K ratio and Neutrino energy", 800, 800);
mk1->Divide(2,0);
//>>>>>>>
//mk1->cd(1);
//TH1F *h1 = new TH1F("h1", "Neutrino energy", 25, 0.1, 30);
//h1->GetXaxis()->SetTitle("E_nu");
//h1->GetYaxis()->SetTitle("Entries");
//h1->SetLineWidth(2);
//h1->SetFillColor(kBlue);
//nt->Draw("Ev >> h1", cut1);


Int_t n = 50; // в обох випадках події де знаменник !=0 < 50
TGraph *gr1 = new TGraph(n,ratio,Energy);
TGraph *gr2 = new TGraph(n, ratiof,Energy);

mk1->cd(1);
gr1->SetLineColor(4);
gr1->SetTitle("ratio Pi/K primary as a Ev function");
gr1->SetLineWidth(1);
gr1->Draw("A*");
mk1->cd(2);
gr2->SetTitle("ratio Pi/K final as a Ev function");
gr2->SetLineColor(2);
gr2->SetLineWidth(1);
gr2->Draw("A*");


} 
