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

Float_t ratiof[];// <- проблема тут, якщо впишу vratiof.size() видає помилку,
//якщо створю до цього константу з vratiof.size() все одно помилка, через функції теж нічого не вишло
