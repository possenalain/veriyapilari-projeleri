package Prolab4;


import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;


public class MainAgac{

	KategoriAgaci kategoriAgaci;
	MainAgac(){
		kategoriAgaci=new KategoriAgaci();
	}
		
	public void dosyadan() throws IOException {
		
		FileReader fr;
		String line=null;
		BufferedReader reader=null;

		//int i=1;

		try{
			fr=new FileReader("rezervasyon.txt");
			reader=new BufferedReader(fr);
			//line=reader.readLine();

			while((line=reader.readLine())!=null) {

				if(line.equalsIgnoreCase("")) {
					continue;
				}


				/*
				 * userid,placeid,datetime,lat,lon,city,category
				 */

				String splitted[]=line.split(",");


				//KATEGORI YOKSA EKLE

				Kategori k=initializeKategori(splitted);
				k=this.kategoriAgaci.addKnode(k);

				//KULLANICI EKLEMELER
				if(k!=null) {
					Kullanici U=initializeKullanici(splitted);
					U.setKategoriIsimi(k.getKategoriIsmi());
					
					U=k.AddKullanici(U);
					U.setBaba(k);
					
					if(U!=null) {//EKLENDI YA DA VARDI
						
					//REZERVASYON EKLENMESI

				     U.addRezervasyon(splitted);
					}
					
				}
			}
		}catch(IOException e) {}
		finally {
			if(reader!=null) reader.close();

		}
	}
	
	private Kullanici initializeKullanici(String[] splitted) {

		String kullaniciId=(String)splitted[0];
		//int rezervasyonsayisi;

		Kullanici K=new Kullanici();
		K.setKullaniciId(kullaniciId.trim());	
		return K;	
	}

	private Kategori initializeKategori(String[] splitted) {

		String tempcategory=(String)splitted[6];
		String categorysplitted[]=tempcategory.split(":");

		int isimIndex=categorysplitted.length-1;


		Kategori k=new Kategori();
		k.setKategoriIsmi((String) categorysplitted[isimIndex].trim());
		k.setKategoriYolu((String) splitted[6].trim());
		
		return k;
	}
	
	public void Bilgi() {
		kategoriAgaci.kategoriRoot.bilgi();
	}
		
public void KullaniciyaKategoriListeleme(Kategori Root, int offset ,String KullaniciId) {
	/*
	 * if(kategoriRoot.getAltKategoriSayisi()==0) { //KATEGORI AGACI BOS return
	 * kategoriRoot; }
	 */

	Kategori altKategori;
	altKategori=Root.altKategoriler.get(offset);

	if(altKategori.kullaniciAgaci.kullanicilar.size()>0) {//
		for(int i=0;i<altKategori.kullaniciAgaci.kullanicilar.size();i++) {
			if(altKategori.kullaniciAgaci.kullanicilar.get(i).getKullaniciId().equals(KullaniciId)) {
				if(altKategori==(altKategori.kullaniciAgaci.kullanicilar.get(i).Babam)) {
					//System.out.println(" "+altKategori.getKategoriYolu());
					
					altKategori.bilgi();
					break;
					}	
			}

		}
		//altKategori.RemoveKullanici(KullaniciId);
		
	}


	if(offset+1<Root.getAltKategoriSayisi()) {
		KullaniciyaKategoriListeleme(Root,offset+1,KullaniciId);
	}


	if(altKategori.getAltKategoriSayisi()>0) {	
		KullaniciyaKategoriListeleme(altKategori,0,KullaniciId);
	}
}

public void RezervasyonYerineKullaniciListele(Kategori Root, int offset ,String RezervasyonYeri) {
	/*
	 * if(kategoriRoot.getAltKategoriSayisi()==0) { //KATEGORI AGACI BOS return
	 * kategoriRoot; }
	 */

	Kategori altKategori;
	altKategori=Root.altKategoriler.get(offset);

	if(altKategori.kullaniciAgaci.kullanicilar.size()>0) {//
		for(int i=0;i<altKategori.kullaniciAgaci.kullanicilar.size();i++) {
			Kullanici KulTemp=altKategori.kullaniciAgaci.kullanicilar.get(i);
			if(KulTemp.getRezervasyonSayisi()>0) {
				Rezervasyon RzTemp=KulTemp.RzListi.RootRz;
				
				while(RzTemp!=null) {
					
					if(RzTemp.getYerId().equals(RezervasyonYeri)) {
						System.out.println(" "+KulTemp.getKullaniciId());
						//altKategori.bilgi();
						break;
						
						}
			  RzTemp=RzTemp.getNextRezervasyon();
				}	
			}

		}
		//altKategori.RemoveKullanici(KullaniciId);
		
	}


	if(offset+1<Root.getAltKategoriSayisi()) {
		RezervasyonYerineKullaniciListele(Root,offset+1,RezervasyonYeri);
	}


	if(altKategori.getAltKategoriSayisi()>0) {	
		RezervasyonYerineKullaniciListele(altKategori,0,RezervasyonYeri);
	}
}

}
