{
  gROOT->ProcessLine(".L path.cpp+");
  gROOT->ProcessLine(".L taus.C+");
  auto c1 = new TCanvas("c1","c1",800,800);
  TView3D *view = (TView3D*) TView::CreateView(1);
  view->SetRange(-20,-20,-20,20,20,20);
  TAxis3D rulers;
  rulers.Draw();
  // draw a helix
  double px[10], py[10], pz[10];
  taus(0.1, 0.3, 2.0, 0.05, 4.0, 0.0, 2.0, 10, px, py, pz);
  TPolyLine3D *plh = new TPolyLine3D(10, px, py, pz);
  plh->Draw();
  // draw a line (from the origin)
  double start[] = {0., 0., 0.};
  double dirn[] = {-1., 1., 1.};
  liner(start, dirn, 20., px, py, pz);
  TPolyLine3D *pll = new TPolyLine3D(2);
  pll->SetPoint(0, px[0], py[0], pz[0]);
  pll->SetPoint(1, px[1], py[1], pz[1]);
  pll->Draw();
  // draw the closest approach vector, values taken from output of taus.exe
  TPolyLine3D *pAB = new TPolyLine3D(2);
  pAB->SetPoint(0, -5.2309 , 5.10236 , 6.25 );
  pAB->SetPoint(1, -5.7735 , 5.7735 , 5.7735 );
  pAB->SetLineColor(2);
  pAB->Draw();
}
