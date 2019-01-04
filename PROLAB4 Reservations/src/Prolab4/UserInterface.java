package Prolab4;

import java.io.IOException;
import java.util.Scanner;

public class UserInterface extends MainAgac {

	Scanner scan=new Scanner(System.in);

	UserInterface(){

	}
	//KULLANICI ISLEMLERI
	public  void Kategoriyle() {


		String islem="";

		while(!islem.equalsIgnoreCase("Ana")||!islem.equalsIgnoreCase("0")){

			System.out.println("\n\n-----Kategori islemler------\n");
			System.out.println("Kategori bulma[bulma:1]");
			System.out.println("Ana menusu [ana:0]\n");

			islem=scan.nextLine();

			if(islem.equalsIgnoreCase("bulma")||islem.equalsIgnoreCase("1")) {
				String aranacak;
				System.out.println("bulunacak kategori:");
				aranacak=scan.nextLine();
				Kategori KTemp=kategoriAgaci.KategoriBul(kategoriAgaci.kategoriRoot,0,aranacak);
				if(KTemp!=null) {
					KTemp.bilgi();

					//KATEGORI MINI ISLEMLERI


					String minislem="";

					while(!minislem.equalsIgnoreCase("devam")||!minislem.equalsIgnoreCase("0")){

						System.out.println("\n----"+aranacak+" islemleri---");
						System.out.println("alt Kategori ekleme[ekleme:1]");
						System.out.println("kategori silme[silme:2]");
						System.out.println("devam [devam:0]\n\n");

						minislem=scan.nextLine();
						if(minislem.equalsIgnoreCase("ekleme")||minislem.equalsIgnoreCase("1")) {
							kategoriAgaci.AltkategoriEkle(KTemp);
							break;
						}
						else if(minislem.equalsIgnoreCase("silme")||minislem.equalsIgnoreCase("2")) {
							if(kategoriAgaci.kategoriSilme(kategoriAgaci.kategoriRoot,0,KTemp.getKategoriYolu())) {
								System.out.println("#SILINDI");
							}
							else {
								System.out.println("#SILINMEDI");
							}

							break;
						}
						else if(minislem.equalsIgnoreCase("devam")||minislem.equalsIgnoreCase("0")) {
							break;
						}
					}	
				}
				else {
					System.out.println(aranacak+" Kategorilerden Bulunmadi");
				}
			}

			else if(islem.equalsIgnoreCase("Ana")||islem.equalsIgnoreCase("0")) {
				break;
			}
		}
	}

	private Kategori kategoriYoluIste() {


		Kategori From=kategoriAgaci.kategoriRoot;
		Kategori KTemp=null;


		boolean Kvar=false;

		while(!Kvar) {
			String KategoriYolu="";
			System.out.println("\nkategori yolu:");
			KategoriYolu=scan.nextLine();
			String KategoriIsimleri[]=KategoriYolu.split(":");


			for(int i=0;i<KategoriIsimleri.length;i++){
				KTemp=kategoriAgaci.KategoriBul(From,0,KategoriIsimleri[i]);
				if(KTemp.getAltKategoriSayisi()<1) {
					break;
				}
				From=KTemp;
			}
			if(KTemp!=null) {
				Kvar=true; 
				KTemp.bilgi();
			}
			if(Kvar){
				break;
			}

		}


		return KTemp;
	}

	public void Kullaniciyla() {

		Kategori KTemp=kategoriYoluIste();
		if(KTemp!=null) {

			String minislem="";

			while(!minislem.equalsIgnoreCase("Ana")||!minislem.equalsIgnoreCase("0")){

				System.out.println("\n----kullanici islemleri---");
				System.out.println("bu kategoride tum kullanici silme1[silme1:1]");
				System.out.println("bu kategoride kullaniciyi silme2[silme2:2]");
				System.out.println("agactan kullanici silme3[silme3:3]");
				System.out.println("Kullanici ekleme[ekleme:4]");
				System.out.println("Ana [Ana:0]\n\n");

				minislem=scan.nextLine();
				if(minislem.equalsIgnoreCase("silme1")||minislem.equalsIgnoreCase("1")) {
					KTemp.RemoveAllKullanici();
					break;
				}
				else if(minislem.equalsIgnoreCase("silme2")||minislem.equalsIgnoreCase("2")) {	
					String KullaniciId;
					System.out.println("silinecek Kullanici:");
					KullaniciId=scan.nextLine();
					KTemp.RemoveKullanici(KullaniciId);
					System.out.println("------guncel bu kategorideki kullanici listesi----");
					KTemp.kullaniciAgaci.KullaniciheapDisplay(); 
					break;
				}
				else if(minislem.equalsIgnoreCase("silme3")||minislem.equalsIgnoreCase("3")) {
					String KullaniciId;
					System.out.println("silinecek Kullanici:");
					KullaniciId=scan.nextLine();
					kategoriAgaci.AgactanKullaniciSilme(kategoriAgaci.kategoriRoot, 0,KullaniciId);
					break;
				}
				else if(minislem.equalsIgnoreCase("ekleme")||minislem.equalsIgnoreCase("4")) {
					String KullaniciId;
					System.out.println("Kullanici Id:");
					KullaniciId=scan.nextLine();
					Kullanici newKullanici=new Kullanici();
					newKullanici.setKullaniciId(KullaniciId);
					newKullanici.setKategoriIsimi(KTemp.getKategoriIsmi());
					newKullanici=KTemp.AddKullanici(newKullanici);
					if(newKullanici==null) {
						System.out.println("Eklenmedi");
					}
					else {
						System.out.println("Basariyla eklendi");
						System.out.println("--------------------");
						KTemp.bilgi();
						System.out.println("guncellenmis u kategorideki kullanicilar");
						System.out.println("--------------------");
						KTemp.kullaniciAgaci.KullaniciheapDisplay(); 
					}
					break;
				}
				else if(minislem.equalsIgnoreCase("Ana")||minislem.equalsIgnoreCase("0")) {
					break;
				}
			}

		}


	}

	public  void listelemeler() {

		String islem="";

		while(!islem.equalsIgnoreCase("Ana")||!islem.equalsIgnoreCase("0")){

			System.out.println("\n\n-------------------------------");
			System.out.println("Kullaniciya gore kategori[listele1:1]");
			System.out.println("kategoriye gore kullanici[listele2:2]");
			System.out.println("Rezervasyon yerine gore kullanici[listele3:3]");
			System.out.println("kullaniciya gore rezervasyon[listele4:4]");
			System.out.println("Ana menu [ana:0]\n\n");

			islem=scan.nextLine();

			if(islem.equalsIgnoreCase("listele1")||islem.equalsIgnoreCase("1")) {

				String KullaniciId;
				System.out.println("\nKullanici Id:");
				KullaniciId=scan.nextLine();
				KullaniciyaKategoriListeleme(kategoriAgaci.kategoriRoot, 0,KullaniciId);


			}
			else if(islem.equalsIgnoreCase("listele2")||islem.equalsIgnoreCase("2")) {
				Kategori KTemp=kategoriYoluIste();
				if(KTemp!=null) {
					System.out.println("\n--"+KTemp.getKategoriIsmi()+" deki tum kullanicilar---");
					KTemp.kullaniciAgaci.KullaniciheapDisplay();
				}

			}
			else if(islem.equalsIgnoreCase("listele3")||islem.equalsIgnoreCase("3")) {

				String RezervasyonYeri;
				System.out.println("\nRezervasyon Yeri:");
				RezervasyonYeri=scan.nextLine();
				RezervasyonYerineKullaniciListele(kategoriAgaci.kategoriRoot, 0,RezervasyonYeri);

			}
			else if(islem.equalsIgnoreCase("listele4")||islem.equalsIgnoreCase("4")) {
				Kategori KTemp=kategoriYoluIste();
				if(KTemp!=null) {
					Kullanici KULTemp=null;
					while(KULTemp==null) {

						String KullaniciId;
						System.out.println("\n\nKullanici Id:");
						KullaniciId=scan.nextLine();
						KULTemp=KTemp.kullaniciAgaci.kullaniciBul(KullaniciId);
					}

					if(KULTemp!=null){
						KULTemp.KullaniciBilgi();
						System.out.println("\n--"+KULTemp.getKullaniciId()+" rezervasyonlari--");
						KULTemp.RzListi.RezervasyonListele();
					}

				}
			}
			else if(islem.equalsIgnoreCase("ana")||islem.equalsIgnoreCase("0")) {
				break;
			}



		}


	}

	public static void main(String args[]) throws IOException {

		UserInterface UserI=new UserInterface();
		Scanner scan=new Scanner(System.in);

		UserI.dosyadan();
		UserI.Bilgi();

		String islem="";

		while(!islem.equalsIgnoreCase("exit")||!islem.equalsIgnoreCase("0")){

			System.out.println("-------------------------------");
			System.out.println("Kategori islemler[kategori:1]");
			System.out.println("kullanici islemler[kullanici:2]");
			System.out.println("listeleme islemler[listeleme:3]");
			System.out.println("cikmak [exit:0]\n\n");

			islem=scan.nextLine();
			if(islem.equalsIgnoreCase("kategori")||islem.equalsIgnoreCase("1")) {
				UserI.Kategoriyle();
			}
			else if(islem.equalsIgnoreCase("kullanici")||islem.equalsIgnoreCase("2")) {
				UserI.Kullaniciyla();
			}
			else if(islem.equalsIgnoreCase("listeleme")||islem.equalsIgnoreCase("3")) {
				UserI.listelemeler();
			}
			else if(islem.equalsIgnoreCase("exit")||islem.equalsIgnoreCase("0")) {
				break;
			}

		}
		scan.close();
	}
}
