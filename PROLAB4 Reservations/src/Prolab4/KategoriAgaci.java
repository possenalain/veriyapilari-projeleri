package Prolab4;

import java.util.Scanner;

public class KategoriAgaci {
	Scanner scan=new Scanner(System.in);
	Kategori kategoriRoot;
    
	KategoriAgaci(){

		kategoriRoot=new Kategori();
		kategoriRoot.setKategoriIsmi("rezervasyon");
		kategoriRoot.setKategoriYolu("");
		kategoriRoot=kategoriRoot.addAltKategori(kategoriRoot);

	}

	public Kategori addKnode(Kategori k) {
		k=kategoriRoot.addAltKategori(k);

		if(k!=null) {
			//k.bilgi();
		}

		return k;
	}

	public Kategori KategoriBul(Kategori root ,int offset,String kategoriIsmi) {

		/*
		 * if(kategoriRoot.getAltKategoriSayisi()==0) { //KATEGORI AGACI BOS return
		 * kategoriRoot; }
		 */

		Kategori k=null;
		Kategori altKategori;
		altKategori=root.altKategoriler.get(offset);

		if(altKategori.getKategoriIsmi().equalsIgnoreCase(kategoriIsmi)) {//Bulduk
			k=altKategori;
			return k;

		}


		if(offset+1<root.getAltKategoriSayisi()) {
			//System.out.println("~~~~~~~~~~~~~~~~~~~gectim  :"+altKategori.getKategoriYolu());
			k=KategoriBul(root,offset+1,kategoriIsmi);
			if(k!=null)
				return k;
		}

		if(k==null)
		{	
			if(altKategori.getAltKategoriSayisi()>0) {	
				k=KategoriBul(altKategori,0,kategoriIsmi);
			}

		}

		return k;


	}

	public void AltkategoriEkle(Kategori k) {

		//String kategoriIsmi=k.getKategoriIsmi();
		Kategori yeniKategori;
				if((yeniKategori=yeniKategori(k))!=null) {
					System.out.println("Added successfully");
					yeniKategori.bilgi();
				}
	}


	public Kategori yeniKategori(Kategori root) {


		Kategori k=new Kategori();
		System.out.println("isim");
		String isim="";
		isim=scan.nextLine();
		k.setKategoriIsmi(isim);

		k.setDerinlik(root.getDerinlik()+1);
		if(root.getDerinlik()==0)
			k.setKategoriYolu(root.getKategoriYolu()+isim);
		else
			k.setKategoriYolu(root.getKategoriYolu()+":"+isim);
		root.altKategoriler.add(k);
		root.setAltKategoriSayisi(root.getAltKategoriSayisi()+1);

		return k;
	}

	public boolean kategoriSilme(Kategori root,int offset,String kategoriYolu) {


		boolean silindi=false;
		Kategori altKategori;
		altKategori=root.altKategoriler.get(offset);


		if(altKategori.getKategoriYolu().equalsIgnoreCase(kategoriYolu)) {//Bulduk
			//BULUNDU SIL


			//SILNECEK KATEGORIYI BULDUK


			for(int j=0;j<altKategori.getAltKategoriSayisi();j++) {//ALTKATEGORILERI PARENT'E TAS

				Kategori temp=altKategori.altKategoriler.get(j);

				temp.setDerinlik(root.getDerinlik()+1);

				if(root.getDerinlik()==0)
					temp.setKategoriYolu(root.getKategoriYolu()+temp.getKategoriIsmi());
				else
					temp.setKategoriYolu(root.getKategoriYolu()+":"+temp.getKategoriIsmi());

				root.altKategoriler.add(temp);
				root.setAltKategoriSayisi(root.getAltKategoriSayisi()+1);
			}

			root.altKategoriler.remove(altKategori);
			root.setAltKategoriSayisi(root.getAltKategoriSayisi()-1);
			System.out.println("\n\nBasariyla silindi\nBabasinin bilgileri guncellendi\n\n");
			root.bilgi();

			silindi=true;
			return silindi;
		}


		else if((offset+1<root.getAltKategoriSayisi())) {
			//System.out.println("~~~~~~~~~~~~~~~~~~~gectim :"+altKategori.getKategoriYolu());
			silindi=kategoriSilme(root,offset+1,kategoriYolu);
		}

		if(!silindi)
		{	
			if(altKategori.getAltKategoriSayisi()>0) {	
				silindi=kategoriSilme(altKategori,0,kategoriYolu);
			}

		}

		return silindi;

	}

	public void AgactanKullaniciSilme(Kategori root ,int offset,String KullaniciId) {

		/*
		 * if(kategoriRoot.getAltKategoriSayisi()==0) { //KATEGORI AGACI BOS return
		 * kategoriRoot; }
		 */

		Kategori altKategori;
		altKategori=root.altKategoriler.get(offset);

		if(altKategori.kullaniciAgaci.kullanicilar.size()>0) {//
			altKategori.RemoveKullanici(KullaniciId);
		}


		if(offset+1<root.getAltKategoriSayisi()) {
			AgactanKullaniciSilme(root,offset+1,KullaniciId);
		}


		if(altKategori.getAltKategoriSayisi()>0) {	
			AgactanKullaniciSilme(altKategori,0,KullaniciId);
		}

	}
	
}
