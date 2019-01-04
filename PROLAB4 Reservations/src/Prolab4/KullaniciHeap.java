package Prolab4;

import java.util.ArrayList;

public class KullaniciHeap<T extends Kullanici> {

	 ArrayList<T> kullanicilar;
	Kategori baba;
	KullaniciHeap(){
		kullanicilar=new ArrayList<T>();
		this.baba=null;
	}

	public void HeapifyUp(int index) {
		
		int peakI=index;
		
		while(peakI>0) {
			int parentI=(peakI-1)/2;
			
			T kullanici=kullanicilar.get(peakI);
			T parent=kullanicilar.get(parentI);
			
			if(kullanici.CompareKullanici(parent)) {
				
				//SWAP
				kullanicilar.set(peakI, parent);
				kullanicilar.set(parentI, kullanici);
				
				
				peakI=parentI;
		
				
			}else {
				break;
			}
			
		}
	}
	
	
	public T InsertKullanici(T kullanici) {
		T returned=kullaniciBul(kullanici.getKullaniciId());
		if(returned==null) {
		kullanicilar.add(kullanici);
		HeapifyUp(kullanicilar.indexOf(kullanici));
		returned=kullanici;
		this.baba.KullaniciSayisiArtir();
		
		}
		else {
			//System.out.println("vardi");
			HeapifyUp(kullanicilar.indexOf(returned));
		}
		
		return returned;
	}
		
	public void HeapifyDown(int P){
		int peakI=P;
		int leftI=(peakI*2)+1;
		
		while(leftI<kullanicilar.size()) {
			int maxI=leftI;
			int rightI=leftI+1;
			
			if(rightI<kullanicilar.size()) {//peak at the maximum node 
				if(kullanicilar.get(rightI).CompareKullanici(kullanicilar.get(leftI))) {
					maxI++;
				}	
			}
			
			T max=kullanicilar.get(maxI);
			T peak=kullanicilar.get(peakI);
			if(max.CompareKullanici(peak)) {
				
				//SWAP 
				T temp=max;
			    kullanicilar.set(maxI, peak);
			    kullanicilar.set(peakI, temp);
				
			    peakI=maxI;
			    leftI=(peakI*2)+1;
			    	
			}else {
				break;
			}
			
			
		}
	}
	
	//KULLANICIYI BULMAK ICIN
	public T kullaniciBul(String KullaniciId) {
		for(int i=0;i<this.kullanicilar.size();i++) {
			if(kullanicilar.get(i).getKullaniciId().equalsIgnoreCase(KullaniciId.trim())) {
				//VAR
				return kullanicilar.get(i);
			}
		}
		return null;
	}
	
/*
 * 
 *  KULLANICI SILME
 * 1 ALL
 * 2 KULLANICIYI BULARAK TEK SIL 
 * 3 TUM KATEGORILERDE KULLANICIYI BULARAK TUMUNU SIL
 * (BU MAIN AGACINDA TANIMLANACAK)
 * 
 */
	public void KullaniciSilme1() {
		try {
			
			for(int i=0;i<this.kullanicilar.size();i++) {
				this.baba.KullaniciSayisiAzalt();
				for(int j=0;j<this.kullanicilar.get(i).rezervasyonSayisi;j++)
					this.baba.RezervasyonSayisiAzalt();
			}
				
				
		if(this.kullanicilar.removeAll(kullanicilar)) {
			System.out.println("Done");
		}	
	}catch(NullPointerException e){
		System.out.println("Bos' kullanici Heap");
	};
	}
	
	public void KullaniciSilme2(String KullaniciId) {
		
		T silinecek=kullaniciBul(KullaniciId);
		int silI=0;
		if(silinecek==null) {
		//System.out.print("YOK");
		}
		
		else {
			if(kullanicilar.size()>1) {
				
				int lastI=this.kullanicilar.size()-1;
				silI=this.kullanicilar.indexOf(silinecek);
				T last=kullanicilar.get(lastI);
				this.kullanicilar.set(silI, last);
				this.kullanicilar.set(lastI, silinecek);
				
			}
		
			try {
			   if(this.kullanicilar.remove(silinecek)) {
				  // System.out.println("silindi");
				   this.baba.KullaniciSayisiAzalt();
				   this.baba.RezervasyonSayisiAzalt();
			   }
			}	
		  catch(NullPointerException e){
			System.out.println("sikinti  yasandi");
		  };
		  
		  HeapifyDown(silI);
		}
	}
	
	public void KullaniciheapDisplay() {
		System.out.println("--------------------------------");
		for(int i=0;i<this.kullanicilar.size();i++) {
			System.out.println("\n\n#K"+i);
			kullanicilar.get(i).KullaniciBilgi();
			}
	}
	
}
